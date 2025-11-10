#include "Registry.hpp"
#include "Channel.hpp"
#include "Client.hpp"

// Constructeur
Registry::Registry()
    : _clientsByFd()
    , _clientsByNick()
    , _channelsByName()
{
}

// Constructeur de copie
Registry::Registry(const Registry& other)
    : _clientsByFd(other._clientsByFd)
    , _clientsByNick(other._clientsByNick)
    , _channelsByName()  // On va copier les canaux manuellement
{
    // Copie profonde des canaux
    for (std::map<std::string, Channel*>::const_iterator it = other._channelsByName.begin();
         it != other._channelsByName.end(); ++it) {
        if (it->second != NULL) {
            _channelsByName[it->first] = new Channel(*(it->second));
        }
    }
}

// Opérateur d'assignation
Registry& Registry::operator=(const Registry& other)
{
    if (this != &other) {
        // Nettoyer les canaux existants
        for (std::map<std::string, Channel*>::iterator it = _channelsByName.begin();
             it != _channelsByName.end(); ++it) {
            delete it->second;
        }
        _channelsByName.clear();
        
        // Copier les données simples
        _clientsByFd = other._clientsByFd;
        _clientsByNick = other._clientsByNick;
        
        // Copie profonde des canaux
        for (std::map<std::string, Channel*>::const_iterator it = other._channelsByName.begin();
             it != other._channelsByName.end(); ++it) {
            if (it->second != NULL) {
                _channelsByName[it->first] = new Channel(*(it->second));
            }
        }
    }
    return *this;
}

// Destructeur
Registry::~Registry()
{
    // Supprimer tous les canaux alloués
    for (std::map<std::string, Channel*>::iterator it = _channelsByName.begin();
         it != _channelsByName.end(); ++it) {
        delete it->second;
    }
    _channelsByName.clear();
    
    // Les clients ne sont pas possédés par Registry, donc pas de delete
    _clientsByFd.clear();
    _clientsByNick.clear();
}

// ========= Clients =========

bool Registry::addClient(Client* c)
{
    if (c == NULL) return false;
    
    int fd = c->getFd();
    if (_clientsByFd.find(fd) != _clientsByFd.end()) {
        return false;  // fd déjà présent
    }
    
    _clientsByFd[fd] = c;
    return true;
}

void Registry::removeClient(Client* c)
{
    if (c == NULL) return;
    
    // Retirer de tous les canaux
    removeClientFromAllChannels(c);
    
    // Retirer des index
    _clientsByFd.erase(c->getFd());
    _clientsByNick.erase(c->getNick());
	delete c;
}

Client* Registry::findClientByFd(int fd) const
{
    std::map<int, Client*>::const_iterator it = _clientsByFd.find(fd);
    return (it != _clientsByFd.end()) ? it->second : NULL;
}

Client* Registry::findClientByNick(const std::string& nick) const
{
    std::map<std::string, Client*>::const_iterator it = _clientsByNick.find(nick);
    return (it != _clientsByNick.end()) ? it->second : NULL;
}

bool Registry::canUseNick(const std::string& nick) const
{
    return isValidNick(nick) && (findClientByNick(nick) == NULL);
}

bool Registry::setNick(Client* c, const std::string& newNick,
                      std::string& err, TargetSet* notify)
{
    if (c == NULL) {
        err = "Client invalide";
        return false;
    }
    
    if (!isValidNick(newNick)) {
        err = "Nick invalide";
        return false;
    }
    
    Client* existing = findClientByNick(newNick);
    if (existing != NULL && existing != c) {
        err = "Nick déjà utilisé";
        return false;
    }
    
    // Retirer l'ancien nick de l'index
    _clientsByNick.erase(c->getNick());
    
    // Mettre à jour le nick du client
    c->setNick(newNick);
    
    // Ajouter le nouveau nick à l'index
    _clientsByNick[newNick] = c;
    
    // Remplir la liste de notification si demandée
    if (notify != NULL) {
        nickPropagationRecipients(c, *notify);
    }
    
    return true;
}

// ========= Channels =========

Channel* Registry::findChannel(const std::string& name) const
{
    std::map<std::string, Channel*>::const_iterator it = _channelsByName.find(name);
    return (it != _channelsByName.end()) ? it->second : NULL;
}

Channel* Registry::findOrCreateChannel(const std::string& name)
{
    std::string normalized = normalizeChannelName(name);
    
    Channel* ch = findChannel(normalized);
    if (ch == NULL) {
        ch = new Channel(normalized);
        _channelsByName[normalized] = ch;
    }
    
    return ch;
}

bool Registry::joinChannel(Client* c, const std::string& name,
                          const std::string& key, std::string& err, TargetSet& notify)
{
    if (c == NULL) {
        err = "Client invalide";
        return false;
    }
    
    std::string normalized = normalizeChannelName(name);
    if (!isValidChannelName(normalized)) {
        err = "Nom de canal invalide";
        return false;
    }
    
    Channel* ch = findOrCreateChannel(normalized);
    
    // Vérifier si déjà membre
    if (ch->has(c)) {
        err = "Déjà membre du canal";
        return false;
    }
    
    // Vérifier la clé si nécessaire
    if (ch->hasKey() && ch->getKey() != key) {
        err = "Invalid key";
        return false;
    }
    
    // Vérifier la limite si nécessaire
    if (ch->hasLimit() && ch->size() >= ch->getLimit()) {
        err = "Channel is full";
        return false;
    }
    
    // Vérifier le mode invite-only si nécessaire
    if (ch->hasInviteOnly()) {
        if (ch->isInvited(c))
            ch->removeInvited(c);
        // TODO: Vérifier si le client a été invité
        // Pour l'instant, on refuse l'accès si le canal est invite-only
        else
        {
            err = "Channel is invite only";
            return false;
        }
    }
    
    // Test ///////////////////////////////////////////////////////////////////////////////////////////////
    if (ch->size() == 0 && !key.empty()) // Si on vient de le creer on ajoute +k avec la key renseignee
        ch->setKey(key);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    // Ajouter le membre
    ch->addMember(c);
    
    // Si c'est le premier membre, en faire un opérateur
    if (ch->size() == 1) {
        ch->addOp(c);
    }
    
    // Remplir la liste de notification
    recipientsForChannel(ch, NULL, notify);  // Tous les membres
    
    return true;
}

bool Registry::partChannel(Client* c, const std::string& name,
                          std::string& err, TargetSet& notify)
{
    if (c == NULL) {
        err = "Client invalide";
        return false;
    }
    
    Channel* ch = findChannel(name);
    if (ch == NULL) {
        err = "Canal inexistant";
        return false;
    }
    
    if (!ch->has(c)) {
        err = "Pas membre du canal";
        return false;
    }
    
    // Remplir la liste de notification avant de retirer le membre
    recipientsForChannel(ch, NULL, notify);
    
    // Retirer le membre
    ch->removeMember(c);
    
    // Supprimer le canal s'il devient vide
    if (ch->size() == 0) {
        _channelsByName.erase(name);
        delete ch;
    }
    
    return true;
}

// ========= Modes & Topic =========

bool Registry::setChannelMode_key(Channel* ch, bool add, const std::string& key,
                                 Client* actor, std::string& err, TargetSet& notify)
{
    if (ch == NULL || actor == NULL) {
        err = "Paramètres invalides";
        return false;
    }
    
    if (!ch->isOp(actor)) {
        err = "Privilèges insuffisants";
        return false;
    }
    
    if (add) {
        ch->setKey(key);
    } else {
        ch->clearKey();
    }
    
    recipientsForChannel(ch, NULL, notify);
    return true;
}

bool Registry::setChannelMode_limit(Channel* ch, bool add, size_t limit,
                                   Client* actor, std::string& err, TargetSet& notify)
{
    if (ch == NULL || actor == NULL) {
        err = "Paramètres invalides";
        return false;
    }
    
    if (!ch->isOp(actor)) {
        err = "Privilèges insuffisants";
        return false;
    }
    
    if (add) {
        ch->setLimit(limit);
    } else {
        ch->clearLimit();
    }
    
    recipientsForChannel(ch, NULL, notify);
    return true;
}

bool Registry::setChannelMode_op(Channel* ch, bool add, Client* target,
                                Client* actor, std::string& err, TargetSet& notify)
{
    if (ch == NULL || actor == NULL || target == NULL) {
        err = "Paramètres invalides";
        return false;
    }
    
    if (!ch->isOp(actor)) {
        err = "Privilèges insuffisants";
        return false;
    }
    
    if (!ch->has(target)) {
        err = "Utilisateur pas membre du canal";
        return false;
    }
    
    if (add) {
        ch->addOp(target);
    } else {
        ch->removeOp(target);
    }
    
    recipientsForChannel(ch, NULL, notify);
    return true;
}

bool Registry::setChannelMode_topic(Channel* ch, bool add,
                                   Client* actor, std::string& err, TargetSet& notify)
{
    if (ch == NULL || actor == NULL) {
        err = "Paramètres invalides";
        return false;
    }
    
    if (!ch->isOp(actor)) {
        err = "Privilèges insuffisants";
        return false;
    }
    
    ch->setTopicProtection(add);
    
    recipientsForChannel(ch, NULL, notify);
    return true;
}

bool Registry::setTopic(Channel* ch, const std::string& topic,
                       Client* actor, std::string& err, TargetSet& notify)
{
    if (ch == NULL || actor == NULL) {
        err = "Paramètres invalides";
        return false;
    }
    
    if (!ch->has(actor)) {
        err = "Pas membre du canal";
        return false;
    }
    
    // Vérifier les restrictions du mode +t (topic protection)
    if (ch->hasTopicProtection() && !ch->isOp(actor)) {
        err = "Seuls les opérateurs peuvent changer le topic (mode +t actif)";
        return false;
    }
    
    ch->setTopic(topic);
    
    recipientsForChannel(ch, NULL, notify);
    return true;
}

bool Registry::setChannelMode_invite(Channel* ch, bool add,
                                    Client* actor, std::string& err, TargetSet& notify)
{
    if (ch == NULL || actor == NULL) {
        err = "Paramètres invalides";
        return false;
    }
    
    if (!ch->isOp(actor)) {
        err = "Privilèges insuffisants";
        return false;
    }
    
    ch->setInviteOnly(add);
    
    recipientsForChannel(ch, NULL, notify);
    return true;
}

// ========= Diffusion utilitaire =========

void Registry::recipientsForChannel(Channel* ch, Client* except, TargetSet& out) const
{
    if (ch == NULL) return;
    
    out.users.clear();
    
    // Ajouter tous les membres du canal sauf 'except'
    for (std::map<int, Client*>::const_iterator it = _clientsByFd.begin();
         it != _clientsByFd.end(); ++it) {
        Client* c = it->second;
        if (c != except && ch->has(c)) {
            out.users.push_back(c);
        }
    }
}

// ========= Règles / Validation =========

bool Registry::isValidNick(const std::string& nick)
{
    if (nick.empty() || nick.length() > 9) return false;
    
    // Premier caractère doit être une lettre
    if (!std::isalpha(nick[0])) return false;
    
    // Autres caractères doivent être alphanumériques ou '_'
    for (size_t i = 1; i < nick.length(); ++i) {
        if (!std::isalnum(nick[i]) && nick[i] != '_') {
            return false;
        }
    }
    
    return true;
}

bool Registry::isValidChannelName(const std::string& name)
{
    if (name.empty() || name.length() > 50) return false;
    
    // Doit commencer par '#'
    if (name[0] != '#') return false;
    
    // Pas d'espaces, virgules ou caractères de contrôle
    for (size_t i = 1; i < name.length(); ++i) {
        char c = name[i];
        if (c == ' ' || c == ',' || c == '\r' || c == '\n' || c == '\0') {
            return false;
        }
    }
    
    return true;
}

std::string Registry::normalizeChannelName(const std::string& name)
{
    if (name.empty()) return "#";
    
    if (name[0] == '#') {
        return name;
    } else {
        return "#" + name;
    }
}

// ========= Méthodes privées =========

void Registry::removeClientFromAllChannels(Client* c)
{
    if (c == NULL) return;
    
    std::vector<std::string> channelsToDelete;
    
    // Retirer le client de tous les canaux
    for (std::map<std::string, Channel*>::iterator it = _channelsByName.begin();
         it != _channelsByName.end(); ++it) {
        Channel* ch = it->second;
        if (ch != NULL && ch->has(c)) {
            ch->removeMember(c);
            
            // Marquer pour suppression si vide
            if (ch->size() == 0) {
                channelsToDelete.push_back(it->first);
            }
        }
    }
    
    // Supprimer les canaux vides
    for (std::vector<std::string>::iterator it = channelsToDelete.begin();
         it != channelsToDelete.end(); ++it) {
        std::map<std::string, Channel*>::iterator chIt = _channelsByName.find(*it);
        if (chIt != _channelsByName.end()) {
            delete chIt->second;
            _channelsByName.erase(chIt);
        }
    }
}

void Registry::nickPropagationRecipients(Client* c, TargetSet& out) const
{
    if (c == NULL) return;
    
    out.users.clear();
    std::set<Client*> recipients;
    
    // Parcourir tous les canaux pour trouver les voisins
    for (std::map<std::string, Channel*>::const_iterator it = _channelsByName.begin();
         it != _channelsByName.end(); ++it) {
        Channel* ch = it->second;
        if (ch != NULL && ch->has(c)) {
            // Ajouter tous les autres membres de ce canal
            for (std::map<int, Client*>::const_iterator clientIt = _clientsByFd.begin();
                 clientIt != _clientsByFd.end(); ++clientIt) {
                Client* other = clientIt->second;
                if (other != c && ch->has(other)) {
                    recipients.insert(other);
                }
            }
        }
    }
    
    // Convertir le set en vector
    for (std::set<Client*>::iterator it = recipients.begin();
         it != recipients.end(); ++it) {
        out.users.push_back(*it);
    }
}

// Get all channels (for NAMES command without parameters)
const std::map<std::string, Channel*>& Registry::getAllChannels() const
{
    return _channelsByName;
}
