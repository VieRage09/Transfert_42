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


class Client;

class Server
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			static bool							signal;

			in_port_t						port;
			std::string						password;
			sockaddr_in						s_addr;
			int								serv_sfd;

			std::vector<pollfd>				v_poll; // Contient les sfd des client connectes ainsi que celui du serv(en premiere pos)
			std::vector<Client>				v_clients; // A remplacer par registery


		#pragma endregion attributes
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

			void		accept_client();
			void		handle_client(int cli_sfd);

			void		remove_client(int sfd);

			void		close_poll_sockets();

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
