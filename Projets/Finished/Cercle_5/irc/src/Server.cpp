#include "Server.hpp"
#include "Bot.hpp"
#include "CommandHandler.hpp"
#include "utils.hpp"

#include <iostream>
#include <unistd.h>		// for close
#include <cstring>		// for strerror
#include <sstream>
#include <iomanip>
#include <cerrno>

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

bool		Server::_signal = false;
std::string	Server::_version = VERSION;
std::string	Server::_server_name = SERV_NAME; 

Server::Server() : _launch_time(time(NULL)), _port(6667), _password("Password1!"), _serv_sfd(-1), _poll(), _reg(), _bot(new Bot())
{
	_s_addr.sin_family = AF_INET;
	_s_addr.sin_port = htons(_port);
	_s_addr.sin_addr.s_addr = INADDR_ANY;

	std::string	error;
	_bot->autoRegister();
	if (!get_reg_ref().setNick(_bot, _bot->getNick(), error, NULL))
		throw std::runtime_error("Couldn't create bot");

	std::cout << "Server instance created with success:\n"
			  << "- Port = " << this->_port
			  << "- Password = " << this->_password
			  << "- IPv4"
			  << "- Bot = " + _bot->getNick() << std::endl;
}

Server::Server(in_port_t port, std::string password) : _launch_time(time(NULL)), _port(port), _password(password), _serv_sfd(-1),
													   _poll(), _reg(), _bot(new Bot())
{
	if (password.empty())
		throw std::runtime_error("Password cannot be empty");
	for (std::string::iterator it = password.begin(); it != password.end(); ++it)
    {
        if (!std::isprint(static_cast<unsigned char>(*it)))
        {
            throw std::runtime_error("Invalid Password: contains non-printable characters");
        }
    }
	_s_addr.sin_family = AF_INET;
	_s_addr.sin_port = htons(_port);
	_s_addr.sin_addr.s_addr = INADDR_ANY;

	std::string	error;
	_bot->autoRegister();
	if (!get_reg_ref().setNick(_bot, _bot->getNick(), error, NULL))
		throw std::runtime_error("Couldn't create bot");

	std::cout << "Server instance created with success:"
			  << "\n- Port = " << this->_port
			  << "\n- Password = " << this->_password
			  << "\n- IPv4"
			  << "\n- Bot = " + _bot->getNick() << std::endl;
}

Server::~Server() {delete _bot;}

#pragma endregion constructor)s
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods

/**
 * @brief Creates a new pollfd structure and pushes it to poll vector
 * @param fd file descriptor associated to the socket
 * @param events events we want to monitor
 * @param revents returned event
 */
void	Server::push_new_poll(int fd, short events, short revents)
{
	pollfd newPoll;

	newPoll.fd = fd;
	newPoll.events = events;
	newPoll.revents = revents;
	_poll.push_back(newPoll);
}

/**
 * @brief Iterates through _poll to calculate how many clients are connected
 */
size_t	Server::count_clients()
{
	size_t count = 0;

	for (size_t i = 0; i < _poll.size(); i++)
		count++;
	return (count - 1); // On enleve le socket du serv
}

/**
 * @brief Enables or disables POLLOUT event monitoring for the given fd \
 * @brief Prints to cerr if fd is not found
 * @param fd the file descriptor associated to the socker of the client we want to modify
 * @param enable true to enable POLLOUT monitoring, false to disable it
 */
void	Server::monitor_pollout(int fd, bool enable)
{
	for (size_t i = 0; i < _poll.size(); i++)
	{
		if (_poll[i].fd == fd)
		{
			if (enable)
				_poll[i].events |= POLLOUT;
			else
				_poll[i].events &= ~POLLOUT;
			return;
		}
	}
	serv_log("[ERROR] monitor_pollout: fd not found", std::cerr, RED);
}

/**
 * @brief Accepts a new connection request and adds it to the poll vector \
 * @brief Throw runtime_error on error
 */
void	Server::accept_client()
{
	int cli_sfd;
	sockaddr_in cli_addr;
	socklen_t size;

	if (count_clients() >= MAX_CLIENT)
	{
		if ((cli_sfd = accept(_serv_sfd, NULL, NULL)) != -1)
		{
			std::string err_serv_full = "[ERROR] Server is full\r\n";
			send(cli_sfd, err_serv_full.c_str(), err_serv_full.size(), MSG_DONTWAIT);
			close(cli_sfd);
		}
		return;
	}
	size = sizeof(cli_addr);
	cli_sfd = accept(_serv_sfd, (sockaddr *)&cli_addr, &size);
	if (cli_sfd == -1)
		return;
	_reg.addClient(new Client(cli_sfd, ""));
	push_new_poll(cli_sfd, POLLIN, 0);
	std::ostringstream oss;
	oss << "New client connected [" << count_clients() << "]";
	serv_log(oss.str(), std::cout, GREEN);
}

/**
 * @brief Calls recv to receive client msg then appends it to the _rBuff of cli \
 * @brief If recv returns 0 (EOF) or -1 (error), closes the connection to that client
 * @param cli A pointer to the client that sent the msg
 */
void	Server::handle_readable(Client *cli)
{
	char buffer[BUFFER_SIZE];
	ssize_t size;

	if (!cli)
	{
		serv_log("[ERROR] handle_client: Client not found", std::cerr, RED);
		return;
	}

	while ((size = recv(cli->getFd(), buffer, BUFFER_SIZE - 1, MSG_DONTWAIT)) > 0 && Server::_signal == false)
	{
		buffer[size] = '\0';
		cli->getRBuffRef().append(buffer);
	}
	cli->touchActivity();
	if (size == 0)
	{
		serv_log("Client disconnected (EOF)", std::cout, GREEN);
		cli->setState(QUIT);
		return;
	}
	if (size == -1)
	{
		serv_log("Message received:\n" + cli->getRBuff(), std::cout, YELLOW);
		parse_cli_buff(cli);
		return;
	}
}

/**
 * @brief Reads the client's _rBuff, executes then erases each block ending with \r\n
 * @brief until it's empty or no \r\n remains
 * @param cli A pointer to the client that need its _rBuff to be parsed
 */
void	Server::parse_cli_buff(Client *cli)
{
	size_t pos;
	std::string line;
	std::string &rBuff = cli->getRBuffRef();

	while (!rBuff.empty() && ((pos = rBuff.find("\r\n")) != std::string::npos))
	{
		line = rBuff.substr(0, pos);
		rBuff.erase(0, pos + 2);
		CommandHandler::handleCommand(this, cli, line);
	}
}

/**
 * @brief Checks if client's sBuff is empty \
 * @brief If not, calls send to send the content of the _sBuff of cli \
 * @brief If an error occurs, closes the connection to that client
 * @param cli A pointer to the client that need its _sBuff to be sent
 */
void	Server::handle_writable(Client *cli)
{
	ssize_t size;

	if (!cli)
	{
		serv_log("[ERROR] handle_writable: Client not found", std::cerr, RED);
		return;
	}
	if (cli->getSBuffRef().empty())
		return;

	while ((size = send(cli->getFd(), cli->getSBuffRef().c_str(), cli->getSBuffRef().size(), MSG_DONTWAIT)) > 0 && Server::_signal == false)
	{
		serv_log("Sent to " + cli->getNick() + ":\n" + cli->getSBuffRef().substr(0, size), std::cout, CYAN);
		cli->getSBuffRef().erase(0, size);
	}
	if (size == -1)
	{
		std::ostringstream	oss;
		oss << "[ERROR] write_client: Failed to send data to client (fd: " << cli->getFd() << "): " << strerror(errno);
		serv_log(oss.str(), std::cerr, RED);
		close_poll(cli->getFd());
		_reg.removeClient(cli);
		return;
	}
	if (cli->getSBuffRef().empty())
		monitor_pollout(cli->getFd(), false);
}

/**
 * @brief Generates a token based on time() and stores it in cli \
 * @brief Sends a ping to cli
 * @param cli A pointer to the client we want to ping
 */
void	Server::ping_client(Client *cli)
{
	std::string	token;
	std::ostringstream oss;

	serv_log("Sending ping to " + cli->getNick(), std::cout, BLUE);
	// generate token
	oss << std::time(NULL);
	token = oss.str();
	cli->setPingToken(token);
	cli->touchPing(token);
	append_client_sBuff(cli, "PING " + token + "\r\n");
}

/**
 * @brief go through all sockets linked to clients \
 * @brief Check if each of them is under the time limit of the different timeouts \
 * @brief If they are in TO zone, they get disconnected \
 * @brief Check if some client are in KILLED or QUIT state and disconnect them
 */
void	Server::check_timeout()
{
	Client *	cli;

	serv_log("Check timeouts ...", std::cout, BLUE);
	for (size_t i = 1; i < _poll.size(); i++)
	{
		cli = _reg.findClientByFd(_poll[i].fd);

		if (!cli)
		{
			serv_log("[ERROR] check_timeout: client not found", std::cerr, RED);
			close_poll(_poll[i].fd);
			continue ;
		}
		if (cli->getState() < REGISTERED)
		{
			if (std::time(NULL) - cli->getLastPing() > RGSTR_TO / 1000)
			{
				serv_log(cli->getNick() + " registration TO", std::cout, MAGENTA);

				std::vector<std::string> params;

				params.push_back("Registration timeout");
				CommandHandler::handleQuit(this, cli, params);

   			    std::string kill_msg = ":" + Server::get_server_name() + " KILL " + ":Registration time out\r\n";

				send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
				cli->setState(KILLED);
			}
		}
		else if (!cli->isWaitingPong() && std::time(NULL) - cli->getLastActivity() >  ACTIVITY_TO / 1000) // a bien checker
			ping_client(cli);
		else if (cli->isWaitingPong() && std::time(NULL) - cli->getLastPing() >  PING_TO / 1000) // a bien checker
		{
			serv_log(cli->getNick() + " ping TO", std::cout, MAGENTA);

			std::vector<std::string> params;
			params.push_back("Ping timeout");
			CommandHandler::handleQuit(this, cli, params);
			
			std::string kill_msg = ":" + Server::get_server_name() + " KILL " + ":Ping time out\r\n";

			send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
			cli->setState(KILLED);
		}
		if (cli->getState() >= QUIT)
		{
			if (cli->getState() == KILLED)
			{
				if (!cli->getNick().empty())
					serv_log(cli->getNick() + " was killed by server", std::cout, GREEN);
				else
					serv_log("* was killed by server", std::cout, GREEN);
			}
			if (cli->getState() == QUIT)
				serv_log(cli->getNick() + " has quit the server", std::cout, GREEN);
           	close_poll(cli->getFd());
			_reg.removeClient(cli);
		}
	}

}

#pragma endregion pmethods
//================================================================================================//

//=============================================================================== METHODS ========//
#pragma region methods

/**
 * @brief Used to turn the _signal attribute of Server to true
 * @param sig number of the received signal
 */
void	Server::handle_signal(int sig)
{
	std::cout << "Signal received: " << sig << std::endl;
	_signal = true;
}

// UTILS
/**
 * @brief Returns a date formated string of _launch_time;
 */
const std::string		Server::get_str_lTime() const
{
    std::ostringstream	oss;
    std::tm*			timeinfo = std::localtime(&_launch_time);
    
	oss	<< std::setfill('0')
    	<< std::setw(2) << timeinfo->tm_mday << "-"
        << std::setw(2) << timeinfo->tm_mon + 1 << "-"
        << timeinfo->tm_year + 1900 << " "
        << std::setw(2) << timeinfo->tm_hour << ":"
        << std::setw(2) << timeinfo->tm_min << ":"
        << std::setw(2) << timeinfo->tm_sec;
    
    return oss.str();
}

/**
 * @brief Sets up the server socket (creation, bind, listen)
 */
void	Server::init_serv()
{
	serv_log("Server initialization ...", std::cout, BLUE);
	_serv_sfd = socket(_s_addr.sin_family, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_serv_sfd == -1)
	{
		std::string err = strerror(errno);
		throw std::runtime_error("Failed to create socket: " + err);
		return;
	}
	// Je comprends pas a quoi sert cette ligne en sah mais askip c'est important
	int opt = 1;
	if (setsockopt(_serv_sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		std::string err = strerror(errno);
		throw std::runtime_error("Failed to set socket options: " + err);
		close(_serv_sfd);
		return;
	}
	if (bind(_serv_sfd, (sockaddr *)&_s_addr, sizeof(_s_addr)) == -1)
	{
		std::string err = strerror(errno);
		throw std::runtime_error("Failed to bind socket: " + err);
		close(_serv_sfd);
		return;
	}
	if (listen(_serv_sfd, SOMAXCONN) == -1) // Cb de max connexions ?
	{
		std::string err = strerror(errno);
		throw std::runtime_error("Failed to listen on socket: " + err);
		close(_serv_sfd);
		return;
	}
	push_new_poll(_serv_sfd, POLLIN, 0);
	serv_log("Server initialization success", std::cout, GREEN);
}

/**
 * @brief Main loop of the server \
 * @brief Runs until SIGSTOP or SIGINT is received \
 * @brief Uses poll to handle events of the sockets fd:
 * @brief - New connection --> calls accept_client()
 * @brief - Message from connected client --> calls handle_client()
 */
void Server::loop()
{
	Client *cli;
	int pol_ret;

	serv_log("Engaging looop ...", std::cout, BLUE);
	while (Server::_signal == false)
	{
		// Le programme est bloque ici par poll jusqu'a ce qu'une operation soit possible
		// sur un des sfd de v_sfd ou la fin du POLLTO
		serv_log("Waiting poll ...", std::cout, BLUE);
		pol_ret = poll(_poll.data(), _poll.size(), POLL_TO);
		if (pol_ret == -1 && Server::_signal == false)
			throw std::runtime_error("poll failed");
		for (size_t i = 0; i < _poll.size(); i++)
		{
			if (_poll[i].revents & POLLIN) // There is data to read
			{
				if (_poll[i].fd == _serv_sfd) // Nouvelle requete de connexion d'un client
					accept_client();
				else // Un client deja co veux interagir
				{
					cli = _reg.findClientByFd(_poll[i].fd);
					if (cli)
						handle_readable(cli);
					else
						serv_log("[ERROR] Loop(read): Client not found in the registry", std::cout, RED);
				}
			}
			if (_poll[i].revents & POLLOUT) // Ready to send data
			{
				if (_poll[i].fd != _serv_sfd)
				{
					cli = _reg.findClientByFd(_poll[i].fd);
					if (cli)
						handle_writable(cli);
					else
						serv_log("[ERROR] Loop(write): Client not found in the registry", std::cout, RED);
				}
			}
		}
		check_timeout();
	}
}

/**
 * @brief Appends str to the _sBuff of cli and enables POLLOUT monitoring if _sBuff is not empty
 * @param cli A pointer to the client that need its _sBuff to be appended
 * @param str The string to append to the _sBuff of cli
 */
void	Server::append_client_sBuff(Client *cli, std::string str)
{
	if (!cli)
	{
		serv_log("[ERROR] append_client_sBuff: NULL client", std::cout, RED);
		return ;
	}
	cli->getSBuffRef().append(str);
	if (!cli->getSBuffRef().empty())
		monitor_pollout(cli->getFd(), true);
}

/**
 * @brief Sends str to all the clients of chan except cli
 * @param chan	Channel target of the message
 * @param cli	Client origin of the message
 * @param str	Message to send, already formatted
 */
void	Server::send_to_channel(Channel * chan, Client * cli, std::string str)
{	
    TargetSet   targetSet;

	_reg.recipientsForChannel(chan, cli, targetSet);
	for (size_t i = 0; i < targetSet.users.size(); i++)
		append_client_sBuff(targetSet.users[i], str);
}

/**
 * @brief Sends str to all the clients of trgSet
 * @param trgSet	list of targets of the message
 * @param str		Message to send, already formatted
 */
void	Server::send_to_targetSet(TargetSet & trgSet, std::string str)
{
	for (size_t i = 0; i < trgSet.users.size(); i++)
		append_client_sBuff(trgSet.users[i], str);
}

/**
 * @brief Close the fd and delete the corresponding pollfd struct from _v_poll \
 * @brief Prints to cerr if fd is not found
 * @param fd the file descriptor associated to the socker of the client we want to close
 */
void	Server::close_poll(int fd)
{
	for (std::vector<pollfd>::iterator it = _poll.begin(); it != _poll.end(); it++)
	{
		if (it->fd == fd)
		{
			_poll.erase(it);
			close(fd);
			return ;
		}
	}
	serv_log("[ERROR] close_poll: fd not found", std::cout, RED);
}

/**
 * @brief Deletes all clients of _reg and close all sockets of _poll
 */
void	Server::shutdown()
{
	serv_log("Shutdown initiated ...", std::cout, BLUE);
	for (size_t i = 1; i < _poll.size(); i++)
		_reg.removeClient(_reg.findClientByFd(_poll[i].fd));
	for (size_t i = 0; i < _poll.size(); i++)
		close(_poll[i].fd);
	_poll.clear();
	serv_log("Shutdown SUCCESS", std::cout, GREEN);
}

#pragma endregion methods
//================================================================================================//

//=============================================================================== GETTERS ========//
#pragma region getters

const std::string &		Server::get_server_name() { return (_server_name); }
const std::string &		Server::get_version() { return (_version); }
const in_port_t &		Server::get_port() const { return (_port); }
const std::string &		Server::get_password() const { return (_password); }
const sockaddr_in &		Server::get_s_addr() const { return (_s_addr); }
const int &				Server::get_serv_sfd() const { return (_serv_sfd); }
const Registry &		Server::get_reg() const { return (_reg); }
Registry &				Server::get_reg_ref() { return (_reg); }

#pragma endregion getters
//================================================================================================//