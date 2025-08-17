#include "Server.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

Server::Server() {}

Server::Server( ) {}

Server::Server(const Server& copy) {}

Server::~Server() {}


#pragma endregion constructors
//================================================================================================//


//=============================================================================== METHODS ========//
#pragma region methods


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
const int&	Server::getserv_sfd() const { return ( serv_sfd );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

void	Server::setport(in_port_t& value) { this->port = value; }
void	Server::setpassword(std::string& value) { this->password = value; }
void	Server::sets_addr(sockaddr_in& value) { this->s_addr = value; }
void	Server::setserv_sfd(int& value) { this->serv_sfd = value; }

#pragma endregion setters
//================================================================================================//

