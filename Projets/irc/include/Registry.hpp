#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <string>
#include <map>
#include <vector>
#include <set>
#include <cstddef>  // size_t
// # include "Channel.hpp"

class Client;

// Ensemble de destinataires à notifier (A enverra réellement)
struct TargetSet {
  std::vector<Client*> users;
};

class Registry {
public:
  Registry();
  ~Registry();

  // ========= Clients =========

  // Enregistre un client fraîchement accepté (A appelle addClient juste après accept()).
  // Ne devient pas "propriétaire" de c (A gère la durée de vie) ; retourne false si fd déjà présent.
  bool          addClient(Client* c);

  // Retire le client de toutes les structures (tous les canaux, index de nick, etc.).
  // A DOIT appeler removeClient(c) avant de fermer le fd et delete c.
  void          removeClient(Client* c);

  // Lookup par fd / par nick
  Client*       findClientByFd(int fd) const;
  // Client*       findClientByNick(const std::string& nick) const;

  // // Vérifie que le nick est syntaxiquement valide ET non utilisé actuellement.
  // bool          canUseNick(const std::string& nick) const;

  // // Applique un changement de nick (après validations par B si besoin).
  // // Remplit notify (optionnel) avec les voisins à prévenir (tous les membres des canaux du client).
  // // Retourne false et renseigne err en cas d’échec (collision, nick invalide…).
  // bool          setNick(Client* c, const std::string& newNick,
  //                       std::string& err, TargetSet* notify /*=0*/);

  // // ========= Channels =========

  // // Trouve un canal existant (0 si absent)
  // Channel*      findChannel(const std::string& name) const;

  // // Normalise le nom (ex: ajoute '#' si absent), crée si besoin, puis retourne le pointeur.
  // Channel*      findOrCreateChannel(const std::string& name);

  // // JOIN avec application des modes (+k : key, +l : limit).
  // // Remplit notify avec la liste des membres à qui diffuser les messages liés (JOIN / NAMES / etc.).
  // // Retourne false + err si refusé (mauvaise key, canal plein, nom invalide…).
  // bool          joinChannel(Client* c, const std::string& name,
  //                           const std::string& key, std::string& err, TargetSet& notify);

  // // PART (ou KICK orchestré par B) : retire c du canal.
  // // Remplit notify avec les membres impactés (diffusions PART/KICK).
  // // Supprime le canal s’il devient vide.
  // bool          partChannel(Client* c, const std::string& name,
  //                           std::string& err, TargetSet& notify);

  // // ========= Modes & Topic =========
  // // Les 3 setters MODE vérifient les permissions (actor doit être op) et modifient l’état.
  // // Ils remplissent notify avec les membres à informer.

  // // +k / -k (clé du canal)
  // bool          setChannelMode_key(Channel* ch, bool add, const std::string& key,
  //                                  Client* actor, std::string& err, TargetSet& notify);

  // // +l / -l (limite de membres)
  // bool          setChannelMode_limit(Channel* ch, bool add, size_t limit,
  //                                    Client* actor, std::string& err, TargetSet& notify);

  // // +o / -o (donner/retirer opérateur à target)
  // bool          setChannelMode_op(Channel* ch, bool add, Client* target,
  //                                 Client* actor, std::string& err, TargetSet& notify);

  // // TOPIC : définit le topic (selon règles, ex: réservé aux ops si canal verouillé)
  // bool          setTopic(Channel* ch, const std::string& topic,
  //                        Client* actor, std::string& err, TargetSet& notify);

  // // ========= Diffusion utilitaire =========

  // // Calcule les destinataires d’un PRIVMSG vers un canal (sauf l’émetteur 'except').
  // void          recipientsForChannel(Channel* ch, Client* except, TargetSet& out) const;

  // // ========= Règles / Validation =========

  // // Validation syntaxique (RFC-like simplifiée) du nick et du nom de canal.
  // static bool   isValidNick(const std::string& nick);
  // static bool   isValidChannelName(const std::string& name);

  // // Normalisation du nom de canal (ex: forcer préfixe '#')
  // static std::string normalizeChannelName(const std::string& name);

private:
  // Index principaux (C n’est PAS propriétaire des Client* ; il possède les Channel*)
  std::map<int, Client*>            _clientsByFd;
  // std::map<std::string, Client*>    _clientsByNick;
  // std::map<std::string, Channel*>   _channelsByName;

  // Retire c de tous les canaux, supprime les canaux devenus vides.
  // void          removeClientFromAllChannels(Client* c);

  // Remplit 'out' avec tous les voisins de c (union des membres de ses canaux), except c lui-même.
  // void          nickPropagationRecipients(Client* c, TargetSet& out) const;
};

#endif // REGISTRY_HPP
