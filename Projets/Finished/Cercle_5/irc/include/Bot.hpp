#ifndef	BOT_HPP
#define	BOT_HPP

// includes //
#include "Client.hpp"
#include <string>

// Forward declarations //
class Server;

class Bot : public Client
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

		std::string									_name;

		#pragma endregion attributes
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Bot();
			~Bot();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

			virtual bool							isBot() const;
			void									autoRegister();
			void									processMsg(Server *serv, Client *cli, std::string & msg);

		#pragma endregion methods
		//==========================================================//
};

#endif // BOT_HPP
