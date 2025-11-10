#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"
#include <string>
#include <ctime>

class Channel;
class Server;

typedef enum clientState{
  WAITING_PASS,
  WAITING_NICK,
  WAITING_USER,
  REGISTERED,
  QUIT,
  KILLED
}clientState;

class Client {
public:
  // Constructeur
  Client(int fd, const std::string& host);
  
  // Norme coplienne
  Client(const Client& other);                    // Constructeur de copie
  Client& operator=(const Client& other);         // Opérateur d'assignation
  virtual ~Client();                              // Destructeur

  // --- Identité réseau / IO ---
  int                   getFd() const;
  const std::string&    getHost() const;
  void                  setHost(const std::string&);

  // --- Identité IRC ---
  const std::string&    getNick() const;
  void                  setNick(const std::string&);

  const std::string&    getUser() const;
  void                  setUser(const std::string&);

  const std::string&    getReal() const;          // alias "realname"
  void                  setReal(const std::string&);

  const std::string	getFullHostMask() const;

  // --- Authentification PASS / état d’enregistrement ---
  void                  setPassOk(bool v);
  bool                  passOk() const;
  bool                  isRegistered() const;   // passOk && _nickSet && _userSet

  // --- Suivi d’activité / PING ---
  void                  touchActivity();        // met à jour _lastActivity = now
  void                  touchPing(std::string token);            // met à jour _lastPing si token est bon
  bool					        isWaitingPong() const;
  void					        setPingToken(std::string token);

  // (optionnel) exposer les timestamps si besoin de debug/timeout
  time_t                getLastActivity() const;
  time_t                getLastPing() const;

  std::string           getRBuff() const;
  std::string           getSBuff() const;
  std::string &         getRBuffRef();
  std::string &         getSBuffRef();

  clientState           getState() const;
  void                  setState(clientState state);
  void                  setFd(int fd);

  virtual bool          isBot() const;

protected:
  // --- Données principales ---
  int           _fd;
  std::string   _host;

  std::string   _nick;
  std::string   _user;
  std::string   _real;

  bool          _passOk;     // true si PASS ok ou non requis
  bool          _nickSet;    // true après setNick()
  bool          _userSet;    // true après setUser()
  clientState   _state;

  // --- Timestamps ---
  time_t        _lastActivity; // maj via touchActivity()
  time_t        _lastPing;     // maj via touchPing()
  std::string   _pingToken;	   // to make sure the received pong is the right one


  std::string   rBuff;
  std::string   sBuff;
};

#endif // CLIENT_HPP
