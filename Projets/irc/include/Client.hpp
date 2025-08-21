#ifndef	CLIENT_HPP
#define	CLIENT_HPP

// includes //
#include "ircserv.hpp"

class Client
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			int								sfd;
			char							send_buff[BUFFER_SIZE];
			char							recv_buff[BUFFER_SIZE];

		#pragma endregion attributes
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Client( int sfd );
			Client(const Client& copy);
			~Client();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

		#pragma endregion methods
		//==========================================================//

		//======================================= OPERATORS ========//
		#pragma region methods

			Client&	operator = (const Client& copy);

		#pragma endregion methods
		//==========================================================//

		//========================================= GETTERS ========//
		#pragma region getters 

			const int&			get_sfd() const;
			const char&			get_send_buff() const;
			const char&			get_recv_buff() const;

		#pragma endregion getters
		//==========================================================//

		//========================================= SETTERS ========//
		#pragma region setters

			void				set_sfd(int& value);
			void				set_send_buff(const char* value); // pas sur du type
			void				set_recv_buff(const char* value);

		#pragma endregion setters
		//==========================================================//

};

#endif // CLIENT_HPP
