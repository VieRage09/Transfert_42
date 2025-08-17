#ifndef	SERVER_HPP
#define	SERVER_HPP

// includes //
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			in_port_t						port;
			std::string						password;
			sockaddr_in						s_addr;
			int								serv_sfd;

		#pragma endregion attributes
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Server();
			Server( );
			Server(const Server& copy);
			~Server();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

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

			void				setport(in_port_t& value);
			void				setpassword(std::string& value);
			void				sets_addr(sockaddr_in& value);
			void				setserv_sfd(int& value);

		#pragma endregion setters
		//==========================================================//

};

#endif // SERVER_HPP
