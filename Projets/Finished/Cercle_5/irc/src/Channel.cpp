#include "../include/Channel.hpp"

// Constructeur
Channel::Channel(const std::string& name)
    : _name(name)
    , _topic("")
    , _key("")
    , _hasKey(false)
    , _limit(0)
    , _hasLimit(false)
    , _topicProtection(false)  // mode +t désactivé par défaut
    , _inviteOnly(false)
    , _members()
    , _ops()
    , _invited()
{
}

// Constructeur de copie
Channel::Channel(const Channel& other)
    : _name(other._name)
    , _topic(other._topic)
    , _key(other._key)
    , _hasKey(other._hasKey)
    , _limit(other._limit)
    , _hasLimit(other._hasLimit)
    , _topicProtection(other._topicProtection)
    , _members(other._members)
    , _ops(other._ops)
    , _invited(other._invited)
{
}

// Opérateur d'assignation
Channel& Channel::operator=(const Channel& other)
{
    if (this != &other) {
        _name = other._name;
        _topic = other._topic;
        _key = other._key;
        _hasKey = other._hasKey;
        _limit = other._limit;
        _hasLimit = other._hasLimit;
        _topicProtection = other._topicProtection;
        _members = other._members;
        _ops = other._ops;
        _invited = other._invited;
    }
    return *this;
}

// Destructeur
Channel::~Channel()
{
    // Rien à faire pour l'instant (pas d'allocation dynamique)
}

// --- Métadonnées ---
const std::string& Channel::getName() const
{
    return _name;
}

// Topic
const std::string& Channel::getTopic() const
{
    return _topic;
}

void Channel::setTopic(const std::string& t)
{
    _topic = t;
}

// --- Membres & privilèges ---
bool Channel::has(Client* c) const
{
    return _members.find(c) != _members.end();
}

bool Channel::isOp(Client* c) const
{
    return _ops.find(c) != _ops.end();
}

void Channel::addMember(Client* c)
{
    if (c != NULL) {
        _members.insert(c);
    }
}

void Channel::removeMember(Client* c)
{
    if (c != NULL) {
        _members.erase(c);
        _ops.erase(c);  // Retire aussi des ops si présent
    }
}

void Channel::addOp(Client* c)
{
    if (c != NULL && has(c)) {  // Doit déjà être membre
        _ops.insert(c);
    }
}

void Channel::removeOp(Client* c)
{
    if (c != NULL) {
        _ops.erase(c);
    }
}

// --- Modes de canal ---
// +k (key)
void Channel::setKey(const std::string& k)
{
    _key = k;
    _hasKey = true;
}

void Channel::clearKey()
{
    _key = "";
    _hasKey = false;
}

bool Channel::hasKey() const
{
    return _hasKey;
}

const std::string& Channel::getKey() const
{
    return _key;
}

// +l (limit)
void Channel::setLimit(size_t n)
{
    _limit = n;
    _hasLimit = true;
}

void Channel::clearLimit()
{
    _limit = 0;
    _hasLimit = false;
}

bool Channel::hasLimit() const
{
    return _hasLimit;
}

size_t Channel::getLimit() const
{
    return _limit;
}

// +t (topic protection)
void Channel::setTopicProtection(bool enable)
{
    _topicProtection = enable;
}

bool Channel::hasTopicProtection() const
{
    return _topicProtection;
}

// +i (invite only channel)

void Channel::setInviteOnly(bool enable)
{
    _inviteOnly = enable;
}

bool Channel::hasInviteOnly() const
{
    return _inviteOnly;
}

bool Channel::addInvited(Client* c) 
{
    std::pair<std::set<Client*>::iterator, bool> result = _invited.insert(c);

    return (result.second);
}

void Channel::removeInvited(Client* c)
{
    _invited.erase(c);
}

bool Channel::isInvited(Client* c) const
{
    return (_invited.find(c) != _invited.end());
}

// --- Infos diverses ---
size_t Channel::size() const
{
    return _members.size();
}

const std::set<Client*>& Channel::getMembers() const
{
    return _members;
}

std::string       Channel::getModeStr() const
{
    std::string modes;

    if (_hasKey)
        modes += "k";
    if (_inviteOnly)
        modes += "i";
    if (_hasLimit)
        modes += "l";
    if (_topicProtection)
        modes += "t";
    if (!modes.empty())
        return ("+" + modes);
    return ("-");
}