#include "Registry.hpp"
#include "Client.hpp"

//============================================================ CONSTRUCTORS & DESTRUCTORS ========//
#pragma region constructors

Registry::Registry() : _clientsByFd() {}

Registry::~Registry() {}

#pragma endregion constructors
//================================================================================================//

//======================================================================= PRIVATE METHODS ========//
#pragma region pmethods

#pragma endregion pmethods
//================================================================================================//

//=============================================================================== METHODS ========//
#pragma region methods

bool          Registry::addClient(Client* c)
{
	// Surement check si on PEUT l'ajouter --> Faut l'authetifier, nick unique etc
	_clientsByFd.insert(std::pair<int, Client *>(c->fd(), c));
	return (true); // A modif par la suite
}

void          Registry::removeClient(Client* c) { _clientsByFd.erase(c->fd()); }

Client*       Registry::findClientByFd(int fd) const
{
	std::map<int, Client *>::const_iterator it = _clientsByFd.find(fd);
	if (it != _clientsByFd.end())
		return (it->second);
	return (NULL);
}

#pragma endregion methods
//================================================================================================//


//============================================================================= OPERATORS ========//
#pragma region operators

#pragma endregion operators
//================================================================================================//


//=============================================================================== GETTERS ========//
#pragma region getters

#pragma endregion getters
//================================================================================================//


//=============================================================================== SETTERS ========//
#pragma region setters

#pragma endregion setters
//================================================================================================//

