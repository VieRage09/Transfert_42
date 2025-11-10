#include "../include/Client.hpp"

// Constructeur
Client::Client(int fd, const std::string& host)
    : _fd(fd)
    , _host(host)
    , _nick("")
    , _user("")
    , _real("")
    , _passOk(false)
    , _nickSet(false)
    , _userSet(false)
    , _state(WAITING_PASS)
    , _lastActivity(std::time(NULL))
    , _lastPing(std::time(NULL))
	, _pingToken("")
{}

// Constructeur de copie
Client::Client(const Client& other)
    : _fd(other._fd)
    , _host(other._host)
    , _nick(other._nick)
    , _user(other._user)
    , _real(other._real)
    , _passOk(other._passOk)
    , _nickSet(other._nickSet)
    , _userSet(other._userSet)
    , _state(other._state)
    , _lastActivity(other._lastActivity)
    , _lastPing(other._lastPing)
	, _pingToken(other._pingToken)
{
    rBuff = other.getRBuff();
    sBuff = other.getSBuff();
}

// Opérateur d'assignation
Client& Client::operator=(const Client& other)
{
    if (this != &other) {
        _fd = other._fd;
        _host = other._host;
        _nick = other._nick;
        _user = other._user;
        _real = other._real;
        _passOk = other._passOk;
        _nickSet = other._nickSet;
        _userSet = other._userSet;
        _state = other._state;
        _lastActivity = other._lastActivity;
        _lastPing = other._lastPing;
		_pingToken = other._pingToken;
        
        rBuff = other.getRBuff();
        sBuff = other.getSBuff();
    }
    return *this;
}

// Destructeur
Client::~Client()
{
    // Rien à faire pour l'instant (pas d'allocation dynamique)
}

// --- Identité réseau / IO ---
int Client::getFd() const
{
    return _fd;
}

const std::string& Client::getHost() const
{
    return _host;
}

void Client::setHost(const std::string& host)
{
    _host = host;
}

// --- Identité IRC ---
const std::string& Client::getNick() const
{
    return _nick;
}

void Client::setNick(const std::string& nick)
{
    _nick = nick;
    _nickSet = true;
}

const std::string& Client::getUser() const
{
    return _user;
}

void Client::setUser(const std::string& user)
{
    _user = user;
    _userSet = true;
}

const std::string& Client::getReal() const
{
    return _real;
}

void Client::setReal(const std::string& real)
{
    _real = real;
}

const std::string	Client::getFullHostMask() const
{
	return (getNick() + "!" + getUser() + "@" + getHost());
}

// --- Authentification PASS / état d'enregistrement ---
void Client::setPassOk(bool v)
{
    _passOk = v;
}

bool Client::passOk() const
{
    return _passOk;
}

bool Client::isRegistered() const
{
    return _passOk && _nickSet && _userSet;
}

// --- Suivi d'activité / PING ---
void Client::touchActivity()
{
    _lastActivity = std::time(NULL);
}

void Client::touchPing(std::string token)
{
	if (_pingToken.compare(token) == 0)
    	_lastPing = std::time(NULL);
}

bool	Client::isWaitingPong() const { return (!_pingToken.empty()); }

void				Client::setPingToken(std::string token) { _pingToken = token; }

time_t				Client::getLastActivity() const { return (_lastActivity); }
time_t				Client::getLastPing() const     { return (_lastPing); }

std::string         Client::getRBuff() const { return (rBuff); }
std::string         Client::getSBuff() const { return (sBuff); }

std::string &       Client::getRBuffRef() { return (rBuff); }
std::string &       Client::getSBuffRef() { return (sBuff); }

clientState         Client::getState() const { return (_state); }
void                Client::setState(clientState state) { _state = state; }
void                Client::setFd(int fd) { _fd = fd; }

bool                Client::isBot() const { return (false); }