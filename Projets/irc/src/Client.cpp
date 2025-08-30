#include "Client.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

Client::Client(int fd, const std::string & host) : _fd(fd), _host(host), _nick(), _user(), _real(),
	_passOk(false), _nickSet(false), _userSet(false)
{
	memset(_rBuff, 0, sizeof(_rBuff));
	memset(_wBuff, 0, sizeof(_wBuff));

	// Ajouter l'init des timestamps
}

#pragma endregion constructors
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods

#pragma endregion pmethods
//================================================================================================//

//=============================================================================== METHODS ========//
#pragma region methods

#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

#pragma endregion operators
//================================================================================================//


//=============================================================================== GETTERS ========//
#pragma region getters

int                   Client::fd() const { return (_fd); }
char  *               Client::rBuff() { return _rBuff; }
#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

#pragma endregion setters
//================================================================================================//

