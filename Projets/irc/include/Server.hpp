#ifndef	SERVER_HPP
#define	SERVER_HPP

// includes //
#include <iostream>
#include <vector>

#include <sys/socket.h> // for socket, bind, listen
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h> // for close
#include <poll.h>	// for poll duh

#include <string.h> // for strerror

class Server
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			in_port_t						port;
			std::string						password;
			sockaddr_in						s_addr;
			int								serv_sfd;
			std::vector<pollfd>		v_sfd;

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

			void	init_serv();
			void	loop();
			void	accept_new_connection();
			void	handle_client(int cli_sfd);

		#pragma endregion methods
		//==========================================================//

		//======================================= OPERATORS ========//
		#pragma region methods

			Server&	operator = (const Server& copy);

		#pragma endregion methods
		//==========================================================//

		//========================================= GETTERS ========//
		#pragma region getters 

			const in_port_t&		getport() const;
			const std::string&		getpassword() const;
			const sockaddr_in&		gets_addr() const;
			const int&				getserv_sfd() const;

		#pragma endregion getters
		//==========================================================//

		//========================================= SETTERS ========//
		#pragma region setters

		#pragma endregion setters
		//==========================================================//

};

#endif // SERVER_HPP
