#ifndef	SERVER_HPP
#define	SERVER_HPP

// includes //
#include "ircserv.hpp"

#include <iostream>
#include <vector>

#include <sys/socket.h> // for socket, bind, listen
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h> // for close
#include <poll.h>	// for poll duh

#include <string.h> // for strerror
#include <signal.h> // for interuption

typedef std::vector<pollfd>		poll_vec;

class Client;
class Registry;

class Server
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			static bool						_signal;

			in_port_t						_port;
			std::string						_password;
			sockaddr_in						_s_addr;
			int								_serv_sfd;

			poll_vec						_poll; // Contient les sfd des client connectes ainsi que celui du serv(en premiere pos)
			// Registry *						_reg;

		#pragma endregion attributes
		//==========================================================//

		//================================= PRIVATE METHODS ========//
		#pragma region pmethods 

			void		push_new_poll(int fd, short events, short revents);
			void		close_poll(int fd);

			void		accept_client();

			void		parser(char *buffer, size_t size, std::string & tmp);
			void		handle_client(Client & cli);

		#pragma endregion pmethods 
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Server();
			Server(in_port_t port, std::string password);
			Server(const Server& copy);
			~Server();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

			static void	handle_signal(int sig);

			void		init_serv();
			void		loop();

			void		close_all_poll();

		#pragma endregion methods
		//==========================================================//

		//======================================= OPERATORS ========//
		#pragma region methods

			Server&	operator = (const Server& copy);

		#pragma endregion methods
		//==========================================================//

		//========================================= GETTERS ========//
		#pragma region getters 

			const in_port_t&		get_port() const;
			const std::string&		get_password() const;
			const sockaddr_in&		get_s_addr() const;
			const int&				get_serv_sfd() const;

		#pragma endregion getters
		//==========================================================//

		//========================================= SETTERS ========//
		#pragma region setters

		#pragma endregion setters
		//==========================================================//

};

#endif // SERVER_HPP
