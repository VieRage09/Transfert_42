#include "Server.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

bool Server::_signal = false;

Server::Server() : _port(6667), _password("Password1!"), _serv_sfd(-1), _poll()
{
	// sfd to -1 because serv socket is not initialized yet
	_s_addr.sin_family = AF_INET;
	_s_addr.sin_port = htons(_port);
	_s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	_s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	// network interfaces on the host => Peut etre bancal
	// _reg = new Registry();
	std::cout	<< "Server instance created with success:\n"
				<< "- Port = " << this->_port
				<< "- Password = " << this->_password
				<< "- IPv4";
}

// TODO: 
// - Make sure port is valid for irc --> portno < 1000 ==> A verifier
// - Politique de mdp ? en vrai balec non ?
Server::Server(in_port_t port, std::string password) : _port(port), _password(password), _serv_sfd(-1),
	_poll()
{
	_s_addr.sin_family = AF_INET;
	_s_addr.sin_port = htons(_port);
	_s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	// network intercaces on the host => Peut etre bancal
	// _reg = new Registry();
	std::cout	<< "Server instance created with success:"
				<< "\n- Port = " << this->_port
				<< "\n- Password = " << this->_password
				<< "\n- IPv4\n";
}

Server::Server(const Server& copy)
{
	_password = copy._password;
}

Server::~Server() {}

#pragma endregion constructors
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods


/**
 * @brief Creates a new pollfd structure and pushes it to poll vector
 * @param fd file descriptor associated to the socket
 * @param events events we want to monitor
 * @param revents returned event
 */
void		Server::push_new_poll(int fd, short events, short revents)
{
	pollfd		newPoll;

	newPoll.fd = fd;
	newPoll.events = events;
	newPoll.revents = revents;
	_poll.push_back(newPoll);
}

/**
 * @brief Close the fd and delete the corresponding pollfd struct from _v_poll \
 * @brief Prints to cerr if fd is not found
 * @param fd the file descriptor associated to the socker of the client we want to close
 * 
 */
void		Server::close_poll(int fd)
{
	close(fd);
	for (std::vector<pollfd>::iterator it = _poll.begin(); it != _poll.end(); it++)
	{
		if (it->fd == fd)
		{
			_poll.erase(it);
			return ;
		}
	}
	std::cerr << "[ERROR] close_poll: fd not found" << std::endl;
}

/**
 * @brief Accepts a new connection request and adds it to the poll vector \
 * @brief Throw runtime_error on error 
 */
void	Server::accept_client()
{
	int			cli_sfd;
	sockaddr_in	cli_addr;
	socklen_t	size;

	std::cout << BLUE << "Accepting new connection..." << RESET << std::endl;
	size = sizeof(cli_addr);
	cli_sfd = accept(_serv_sfd, (sockaddr *)&cli_addr, &size);
	if (cli_sfd == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			std::cout << "No pending connection to accept\n";
			return; // No pending connections
		}
		std::cerr << "[ERROR] accept_client: Failed to accept new connection: " << strerror(errno) << std::endl;
	}
	push_new_poll(cli_sfd, POLLIN, 0);
	// Ajouter au Registry via addClient + check mdp ?
}

void	Server::parser(char *buffer, size_t size, std::string & tmp)
{
	std::string	line;

	buffer[size] = '\0';
	std::cout << "Size = " << size << "\nReceived = " << buffer << std::endl;
	tmp += buffer;
	if (tmp.find("\r\n") != std::string::npos) // \r\n present dans buff
	{
		while (tmp.find("\r\n") != std::string::npos)
		{
			if (tmp.find("\r\n") == tmp.size() - 2) // \r\n a la fin de buffer --> append a line + execution
			{
				line += tmp;
				// Execution ou envoie en file d'attente
				std::cout << "Executing: " << line << std::endl;
				line.clear();
				tmp.clear();
			}
			else
			{
				line += tmp.substr(0, tmp.find("\r\n"));
				// Execution ou envoie en file d'attente
				std::cout << "Execute: " << line << std::endl;
				line.clear();
				tmp = tmp.substr(tmp.find("\r\n") + 2);
			}
		}
	}
	else // pas de \r\n --> On append a line
	{
		line += tmp;
		tmp.clear();
	}
}

/**
 * @brief Uses recv to receive client msg:
 * @brief - normal message --> Sends it to parser function
 * @brief - EOF --> Closes server connection to that client
 * @brief - error --> Closes server connection to that client
 * @param fd file descriptor of the socket that received a msg (of the client)
 */
void	Server::handle_client(Client & cli)
{
	std::string str;
	std::string line;
	size_t		size;
	char *		buff;
	int			pos;

	std::cout << "Handling client msg (fd: " << cli.fd() << ")\n";
	buff = cli.rBuff();
	while ((size = recv(cli.fd(), buff, BUFFER_SIZE - 1, MSG_DONTWAIT)) > 0 && Server::_signal == false)
	{
		buff[size] = '\0';
		str = buff;
		while ((pos = str.find("\r\n")) != std::string::npos)
		{
		}
	}
	if (size == 0)
	{
		std::cout << "Client disconnected (EOF)\n";
		close_poll(cli.fd());
		// _reg.removeClient(_reg.findClientByFd(cli_sfd));
	}
	else if (errno == EAGAIN || errno == EWOULDBLOCK)
	{
		std::cout << "Nothing to read anymore\n";
		return;
	}
	else
	{
		std::cout << "Client disconnected (error): " << strerror(errno) << "\n";
		close_poll(cli.fd());
		// _reg.removeClient(_reg.findClientByFd(cli_sfd));
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

/**
 * @brief Sets up the server socket (creation, bind, listen)
 */
void	Server::init_serv()
{
	std::cout << BLUE << "Initializing Server ..." << RESET << std::endl;
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
	if (bind(_serv_sfd, (sockaddr*)&_s_addr, sizeof(_s_addr)) == -1)
	{
		std::string err = strerror(errno);
		throw std::runtime_error("Failed to bind socket: " + err);
		close(_serv_sfd);
		return;
	}
	if (listen(_serv_sfd, SOMAXCONN) == -1) //Cb de max connexions ?
	{
		std::string err = strerror(errno);
		throw std::runtime_error("Failed to listen on socket: " + err);
		close(_serv_sfd);
		return;
	}
	push_new_poll(_serv_sfd, POLLIN, 0);
	std::cout << GREEN << "Server initialized with success" << RESET << std::endl;
}

/**
 * @brief Main loop of the server \
 * @brief Runs until SIGSTOP or SIGINT is received \
 * @brief Uses poll to handle events of the sockets fd:
 * @brief - New connection --> calls accept_client()
 * @brief - Message from connected client --> calls handle_client()
 */
void	Server::loop()
{
	std::cout << BLUE << "Engaging server loop ..." << RESET << std::endl;
	while (Server::_signal == false)
	{
		// Le programme est bloque ici par poll jusqu'a ce qu'une operation soit possible 
		// sur un des sfd de v_sfd
		if (poll(_poll.data(), _poll.size(), -1) == -1 && Server::_signal == false)
			throw std::runtime_error("poll failed");
		std::cout << "Poll returned, checking for events...\n";
		for (size_t i = 0; i < _poll.size(); i++)
		{
			if (_poll[i].revents & POLLIN)		// There is data to read
			{
				if (_poll[i].fd == _serv_sfd)	// Nouvelle requete de connexion d'un client
					accept_client();
				else							// Un client deja co veux interagir
					handle_client(_poll[i].fd);
			}
		}
	}
}

/**
 * @brief Closes all fd of _poll vector and clears it
 */
void	Server::close_all_poll()
{
	std::cout << BLUE << "Closing all open sockets ..." << RESET << std::endl;
	for (size_t i = 0; i < _poll.size(); i++)
		close(_poll[i].fd);
	_poll.clear();
}

#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

Server& Server::operator = (const Server& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

#pragma endregion operators
//================================================================================================//


//=============================================================================== GETTERS ========//
#pragma region getters

const in_port_t&	Server::get_port() const { return ( _port );}
const std::string&	Server::get_password() const { return ( _password );}
const sockaddr_in&	Server::get_s_addr() const { return ( _s_addr );}
const int&			Server::get_serv_sfd() const { return ( _serv_sfd );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

#pragma endregion setters
//================================================================================================//

