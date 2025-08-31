#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ircserv.hpp"

#include <string>
#include <ctime>   // time_t

class Client {
public:

  Client(int fd, const std::string& host);

  // // --- Identité réseau / IO ---
  int                   fd() const;
  // const std::string&    host() const;

  // // --- Identité IRC ---
  const std::string&    nick() const;
  void                  setNick(const std::string&);

  const std::string&    user() const;
  void                  setUser(const std::string&);

  // const std::string&    real() const;          // alias "realname"
  // void                  setReal(const std::string&);

  // --- Buffers entree sortie ---
  std::string &         rBuff();

  // // --- Authentification PASS / état d’enregistrement ---
  void                  setPassOk(bool v);
  bool                  passOk() const;
  bool                  isRegistered() const;   // passOk && _nickSet && _userSet

  // // --- Suivi d’activité / PING ---
  // void                  touchActivity();        // met à jour _lastActivity = now
  // void                  touchPing();            // met à jour _lastPing = now

  // // (optionnel) exposer les timestamps si besoin de debug/timeout
  // time_t                lastActivity() const { return _lastActivity; }
  // time_t                lastPing() const     { return _lastPing; }

private:
  // --- Données principales ---
  int           _fd;
  std::string   _host;

  std::string   _nick;
  std::string   _user;
  // std::string   _real;

  bool          _passOk;     // true si PASS ok ou non requis
  bool          _nickSet;    // true après setNick()
  bool          _userSet;    // true après setUser()

  std::string   _rBuff;
  // std::string   _wBuff;

  // --- Timestamps ---
  // time_t        _lastActivity; // maj via touchActivity()
  // time_t        _lastPing;     // maj via touchPing()

  
};

#endif // CLIENT_HPP
