#include "Server.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

bool Server::signal = false;

Server::Server() : port(6667), password("Password1!"), serv_sfd(-1), v_poll(), v_clients()
{
	// sfd to -1 because serv socket is not initialized yet
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	// network interfaces on the host => Peut etre bancal
	std::cout	<< "Server instance created with success:\n"
				<< "- Port = " << this->port
				<< "- Password = " << this->password
				<< "- IPv4";
}

// TODO: 
// - Make sure port is valid for irc --> portno < 1000 ==> A verifier
// - Politique de mdp ? en vrai balec non ?
Server::Server(in_port_t port, std::string password) : port(port), password(password), serv_sfd(-1),
	v_poll(), v_clients()
{
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr.s_addr = INADDR_ANY; // A bien check --> socket will be bound to all available
	// network intercaces on the host => Peut etre bancal
	std::cout	<< "Server instance created with success:"
				<< "\n- Port = " << this->port
				<< "\n- Password = " << this->password
				<< "\n- IPv4\n";
}

Server::Server(const Server& copy) : port(copy.port), password(copy.password), serv_sfd(copy.serv_sfd), v_poll(copy.v_poll), v_clients(copy.v_clients)
{
	s_addr.sin_family = copy.s_addr.sin_family;
	s_addr.sin_port = htons(copy.s_addr.sin_port);
	s_addr.sin_addr.s_addr = copy.s_addr.sin_addr.s_addr; // A bien check --> socket will be bound to all available
	// network intercaces on the host => Peut etre bancal
	std::cout	<< "Server instance copied with success:"
				<< "\n- Port = " << this->port
				<< "\n- Password = " << this->password
				<< "\n- IPv4\n";
}

Server::~Server() {}

#pragma endregion constructors
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods

void	Server::accept_client()
{
	int			cli_sfd;
	sockaddr_in	cli_addr;
	socklen_t	size;
	pollfd		newPoll;

	std::cout << "Accepting new connection...\n";
	size = sizeof(cli_addr);
	cli_sfd = accept(serv_sfd, (sockaddr *)&cli_addr, &size);
	if (cli_sfd == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			std::cout << "No pending connection to accept\n";
			return; // No pending connections
		}
		std::cerr << "[ERROR] Failed to accept new connection: " << strerror(errno) << std::endl;
		throw std::runtime_error("client connexion: accept() failed");
	}
	std::cout << "New connection accepted (fd: " << cli_sfd << ")\n";
	newPoll.fd = cli_sfd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;
	v_poll.push_back(newPoll);

	v_clients.push_back(Client(cli_sfd));
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

void	Server::handle_client(int cli_sfd)
{
	char		buffer[BUFFER_SIZE];
	int			size;
	std::string	tmp;

	std::cout << "Handling client msg (fd: " << cli_sfd << ")\n";
	memset((void *)buffer, 0, sizeof(buffer));
	
	while ((size = recv(cli_sfd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT)) > 0 && Server::signal == false)
	{
		parser(buffer, size, tmp);
	}
	if (size == 0)
	{
		std::cout << "Client disconnected (EOF)\n";
		close(cli_sfd);
		remove_client(cli_sfd);
	}
	else if (errno == EAGAIN || errno == EWOULDBLOCK)
	{
		std::cout << "Nothing to read anymore\n";
		return;
	}
	else
	{
		std::cout << "Client disconnected (error): " << strerror(errno) << "\n";
		close(cli_sfd);
		remove_client(cli_sfd);
	}
}

// Surement obsolete si Registery
void	Server::remove_client(int sfd)
{
	for (size_t i = 0; i < v_poll.size(); i++)
	{
  		if (v_poll[i].fd == sfd)
    	{
        	v_poll.erase(v_poll.begin() + i);
        	return;
    	}
	}
	for (size_t i = 0; i < v_clients.size(); i++)
	{
  		if (v_clients[i].get_sfd() == sfd)
    	{
        	v_clients.erase(v_clients.begin() + i);
        	return;
    	}
	}
    std::cout << "Client removed\n";
}

#pragma endregion pmethods
//================================================================================================//

//=============================================================================== METHODS ========//
#pragma region methods

void	Server::handle_signal(int sig)
{
	std::cout << "Signal received: " << sig << std::endl;
	signal = true;
}

// Creates a server socket, binds it to the specified port and starts listening for incoming connections
// Also adds it as the first sfd of v_poll_sfd
void	Server::init_serv()
{
	serv_sfd = socket(s_addr.sin_family, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (serv_sfd == -1)
	{
		std::cerr << "[ERROR] Failed to create socket: " << strerror(errno) << std::endl;
		return;
	}
	// Je comprends pas a quoi sert cette ligne en sah mais askip c'est important
	int opt = 1;
	if (setsockopt(serv_sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		std::cerr << "[ERROR] Failed to set socket options: " << strerror(errno) << std::endl;
		close(serv_sfd);
		return;
	}
	if (bind(serv_sfd, (sockaddr*)&s_addr, sizeof(s_addr)) == -1)
	{
		std::cerr << "[ERROR] Failed to bind socket: " << strerror(errno) << std::endl;
		close(serv_sfd);
		return;
	}
	if (listen(serv_sfd, SOMAXCONN) == -1) //Cb de max connexions ?
	{
		std::cerr << "[ERROR] Failed to listen on socket: " << strerror(errno) << std::endl;
		close(serv_sfd);
		return;
	}

	pollfd	tmp;

	tmp.fd = serv_sfd;
	tmp.events = POLLIN;
	tmp.revents = 0; 
	v_poll.push_back(tmp);
	std::cout << "Server initialized successfully on port " << port << std::endl;
}

// Main loop of the program
// Until SIGSTOP or SIGINT is received, uses poll to handle events of open sfd
// or accept new connections
void	Server::loop()
{
	std::cout << "Engaging server loop ...\n";
	while (Server::signal == false)
	{
		// Le programme est bloque ici par poll jusqu'a ce qu'une operation soit possible 
		// sur un des sfd de v_sfd
		if (poll(v_poll.data(), v_poll.size(), -1) == -1 && Server::signal == false)
			throw std::runtime_error("poll failed");
		std::cout << "Poll returned, checking for events...\n";
		for (size_t i = 0; i < v_poll.size(); i++)
		{
			if (v_poll[i].revents & POLLIN)		// There is data to read
			{
				if (v_poll[i].fd == serv_sfd)	// Nouvelle requete de connexion d'un client
					accept_client();
				else							// Un client deja co veux interagir
					handle_client(v_poll[i].fd);
			}
		}
	}
}

// Close all sockets present inside v_poll
void	Server::close_poll_sockets()
{
	for (size_t i = 0; i < v_poll.size(); i++)
	{
		close(v_poll[i].fd);
	}
	std::cout << "All sockets closed\n";
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

const in_port_t&	Server::get_port() const { return ( port );}
const std::string&	Server::get_password() const { return ( password );}
const sockaddr_in&	Server::get_s_addr() const { return ( s_addr );}
const int&			Server::get_serv_sfd() const { return ( serv_sfd );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

#pragma endregion setters
//================================================================================================//

