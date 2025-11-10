#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ircserv.hpp"
#include <string>
#include <set>

class Client;

class Channel {
public:
  // Constructeur
  explicit Channel(const std::string& name);
  
  // Norme coplienne
  Channel(const Channel& other);                    // Constructeur de copie
  Channel& operator=(const Channel& other);         // Opérateur d'assignation
  ~Channel();                                       // Destructeur

  // --- Métadonnées ---
  const std::string& getName() const;

  // Topic
  const std::string& getTopic() const;
  void               setTopic(const std::string& t);

  // --- Membres & privilèges ---
  bool               has(Client* c) const;     // c ∈ members ?
  bool               isOp(Client* c) const;    // c ∈ ops ?

  void               addMember(Client* c);     // ajoute c à members
  void               removeMember(Client* c);  // retire c de members et de ops si présent
  void               addOp(Client* c);         // nécessite déjà membre
  void               removeOp(Client* c);

  // --- Modes de canal ---
  // +k (key)
  void               setKey(const std::string& k); // active +k et stocke la clé
  void               clearKey();                   // désactive +k
  bool               hasKey() const;               // +k actif ?
  const std::string& getKey() const;               // valeur de la clé (vide si !hasKey)

  // +l (limit)
  void               setLimit(size_t n);           // active +l et fixe la limite
  void               clearLimit();                 // désactive +l
  bool               hasLimit() const;             // +l actif ?
  size_t             getLimit() const;             // valeur de la limite (0 si !hasLimit)

  // +t (topic protection)
  void               setTopicProtection(bool enable); // active/désactive +t
  bool               hasTopicProtection() const;      // +t actif ?

  // +i (invite)
  void                setInviteOnly(bool enable);
  bool                hasInviteOnly() const;

  bool                addInvited(Client* c);
  void                removeInvited(Client* c);
  bool                isInvited(Client* c) const; // c ∈ invited ?

  // --- Infos diverses ---
  size_t             size() const;                 // nombre de membres
  const std::set<Client*>& getMembers() const;    // obtient la liste des membres
  std::string       getModeStr() const;           // Retourne une string indiquant les modes actifs

private:
  std::string        _name;
  std::string        _topic;

  // Modes
  std::string        _key;      bool _hasKey;
  size_t             _limit;    bool _hasLimit;
  bool               _topicProtection;  // mode +t
  bool              _inviteOnly;

  // État
  std::set<Client*>  _members;
  std::set<Client*>  _ops;
  std::set<Client*>  _invited;
};

#endif // CHANNEL_HPP
