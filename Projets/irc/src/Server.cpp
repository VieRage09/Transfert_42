#include "Server.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

bool Server::_signal = false;

Server::Server() : _port(6667), _password("Password1!"), _serv_sfd(-1), _poll(), _reg()
{
	// sfd to -1 because serv socket is not initialized yet
	_s_addr.sin_family = AF_INET;
	_s_addr.sin_port = htons(_port);
	_s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	_s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	// network interfaces on the host => Peut etre bancal
	std::cout	<< "Server instance created with success:\n"
				<< "- Port = " << this->_port
				<< "- Password = " << this->_password
				<< "- IPv4";
}

// TODO: 
// - Make sure port is valid for irc --> portno < 1000 ==> A verifier
// - Politique de mdp ? en vrai balec non ?
Server::Server(in_port_t port, std::string password) : _port(port), _password(password), _serv_sfd(-1),
	_poll(), _reg()
{
	_s_addr.sin_family = AF_INET;
	_s_addr.sin_port = htons(_port);
	_s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	// network intercaces on the host => Peut etre bancal
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

	// Maybe ajouter seulement apres a voir checker via register_client
	std::cout << RED << cli_sfd << RESET << std::endl;
	_reg.addClient(new Client(cli_sfd, "EUH JE SAIS PAS ENCORE"));
}

/**
 * @brief Calls recv to receive client msg then appends it to the _rBuff of cli
 * @return Size of msg read
 * @param cli A pointer to the client that sent the msg
 */
ssize_t	Server::read_client(Client * cli)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		size;

	while ((size = recv(cli->fd(), buffer, BUFFER_SIZE - 1, MSG_DONTWAIT)) > 0 && Server::_signal == false)
	{
		buffer[size] = '\0';
		cli->rBuff().append(buffer);
		std::cout << size << std::endl;
	}
	return (size);
}

void	Server::register_client(Client * cli)
{
	std::string	capls;
	std::string	pass;
	std::string	nick;
	std::string	user;


	capls = cli->rBuff().substr(0, cli->rBuff().find("\r\n"));
	cli->rBuff().erase(0, cli->rBuff().find("\r\n") + 2);
	pass = cli->rBuff().substr(0, cli->rBuff().find("\r\n"));
	cli->rBuff().erase(0, cli->rBuff().find("\r\n") + 2);
	nick = cli->rBuff().substr(0, cli->rBuff().find("\r\n"));
	cli->rBuff().erase(0, cli->rBuff().find("\r\n") + 2);
	user = cli->rBuff().substr(0, cli->rBuff().find("\r\n"));
	cli->rBuff().erase(0, cli->rBuff().find("\r\n") + 2);


	// std::cout << capls << std::endl;
	// std::cout << pass << std::endl;
	// std::cout << nick << std::endl;
	// std::cout << user << std::endl;
}
/**
 * @brief Reads the client's _rBuff, executes then erases each block ending with \r\n 
 * @brief until it's empty or no \r\n remains
 * @param cli A pointer to the client that need its _rBuff to be parsed
 */
void	Server::parse_cli_buff(Client * cli)
{
	size_t		pos;
	std::string	line;

	while (!cli->rBuff().empty() && ((pos = cli->rBuff().find("\r\n")) != std::string::npos))
	{
		line = cli->rBuff().substr(0, pos);
		cli->rBuff().erase(0, pos + 2);
		std::cout << CYAN << "Executing: " << line << RESET << std::endl;
	}
}

/**
 * @brief Uses recv to receive client msg:
 * @brief - normal message --> Sends it to parser function
 * @brief - EOF --> Closes server connection to that client
 * @brief - error --> Closes server connection to that client
 * @param fd file descriptor of the socket that received a msg (of the client)
 */
void	Server::handle_client(Client * cli)
{
	std::string line;
	size_t		size;


	std::cout << "Handling client msg (fd: " << cli->fd() << ")\n";
	size = read_client(cli);
	std::cout << MAGENTA << "Msg received" << RESET << std::endl;
	if (!cli->isRegistered())
		register_client(cli);
	else
		parse_cli_buff(cli);
	if (size == 0)
	{
		std::cout << "Client disconnected (EOF)\n";
		close_poll(cli->fd());
		_reg.removeClient(_reg.findClientByFd(cli->fd()));
	}
	else if (errno == EAGAIN || errno == EWOULDBLOCK)
	{
		std::cout << "Nothing to read anymore\n";
		return;
	}
	else
	{
		std::cout << "Client disconnected (error): " << strerror(errno) << "\n";
		close_poll(cli->fd());
		_reg.removeClient(_reg.findClientByFd(cli->fd()));
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
					handle_client(_reg.findClientByFd(_poll[i].fd));
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

