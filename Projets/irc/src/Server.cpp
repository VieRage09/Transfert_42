#include "Server.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

bool Server::signal = false;

Server::Server() : port(6667), password("Password1!"), serv_sfd(-1), v_sfd(), clients()
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
Server::Server(in_port_t port, std::string password) : port(port), password(password), serv_sfd(-1),
	v_sfd(), clients()
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

Server::Server(const Server& copy) {}

Server::~Server() {}

#pragma endregion constructors
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
	v_sfd.push_back(tmp);
	std::cout << "Server initialized successfully on port " << port << std::endl;
}

void	Server::loop()
{
	std::cout << "Engaging server loop ...\n";
	while (Server::signal == false) // Ajouter de la gestion de signal 
	{
		// Le programme est bloque ici par poll jusqu'a ce qu'une operation soit possible 
		// sur un des sfd de v_sfd
		if (poll(v_sfd.data(), v_sfd.size(), -1) == -1 && Server::signal == false)
			throw std::runtime_error("poll failed");
		std::cout << "Poll returned, checking for events...\n";
		for (int i = 0; i < v_sfd.size(); i++)
		{
			if (v_sfd[i].revents & POLLIN)		// There is data to read
			{
				if (v_sfd[i].fd == serv_sfd)	// Nouvelle requete de connexion d'un client
					accept_new_connection();
				else							// Un client deja co veux interagir
					handle_client(v_sfd[i].fd);
			}
		}
	}
}

void	Server::accept_new_connection()
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
	v_sfd.push_back(newPoll);

	Client		newClient(cli_sfd);
	clients.push_back(newClient);
}

void	Server::handle_client(int cli_sfd)
{
	char		buffer[BUFFER_SIZE];
	int			size;

	std::cout << "Handling client msg (fd: " << cli_sfd << ")\n";
	memset((void *)buffer, 0, sizeof(buffer));
	
	while ((size = recv(cli_sfd, buffer, BUFFER_SIZE - 1, 0)) > 0 && Server::signal == false)
	{
		buffer[size] = '\0';
		std::cout << "Size = " << size << "\nReceived = " << buffer << std::endl;

	}
	if (size == 0)
	{
		std::cout << "Client disconnected (EOF)\n";
		remove_from_poll(cli_sfd);
		close(cli_sfd);
	}
	else
	{
		std::cout << "Client disconnected (error): " << strerror(errno) << "\n";
		remove_from_poll(cli_sfd);
		close(cli_sfd);
	}
}

void	Server::remove_from_poll(int sfd)
{
	// Index-based (always safe)
	for (size_t i = 0; i < v_sfd.size(); i++)
	{
  		if (v_sfd[i].fd == sfd)
    	{
        	v_sfd.erase(v_sfd.begin() + i);
        	std::cout << "Client sfd removed from v_sfd\n";
        	return;
    	}
	}
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

const in_port_t&	Server::getport() const { return ( port );}
const std::string&	Server::getpassword() const { return ( password );}
const sockaddr_in&	Server::gets_addr() const { return ( s_addr );}
const int&			Server::getserv_sfd() const { return ( serv_sfd );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

#pragma endregion setters
//================================================================================================//

