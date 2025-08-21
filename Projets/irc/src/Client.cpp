#include "Client.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

Client::Client(int sfd) : sfd(sfd)
{
	memset(send_buff, 0, BUFFER_SIZE);
	memset(recv_buff, 0, BUFFER_SIZE);
	std::cout << "Client instance created with sfd: " << sfd << std::endl;
}

Client::Client(const Client& copy) {}

Client::~Client() {}


#pragma endregion constructors
//================================================================================================//


//=============================================================================== METHODS ========//
#pragma region methods


#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

Client& Client::operator = (const Client& copy)
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

const int&	Client::get_sfd() const { return ( sfd );}
// const char&	Client::get_send_buff() const { return ( send_buff );}
// const char&	Client::get_recv_buff() const { return ( recv_buff );}

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

void	Client::set_sfd(int& value) { this->sfd = value; }
void	Client::set_send_buff(const char* value) { strncpy(this->send_buff, value, BUFFER_SIZE); }
void	Client::set_recv_buff(const char* value) { strncpy(this->recv_buff, value, BUFFER_SIZE); }

#pragma endregion setters
//================================================================================================//

