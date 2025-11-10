#ifndef	SERVER_HPP
#define	SERVER_HPP

// includes //
#include "ircserv.hpp"
#include "Registry.hpp"
#include "Channel.hpp"

#include <vector>
#include <netinet/in.h> // for sockaddr_in
#include <poll.h>		// for poll duh
#include <ctime>		// for time_t

class Client;
class Bot;

typedef std::vector<pollfd>		poll_vec;


class Server
{
	private:
		//====================================== ATTRIBUTES ========//
		#pragma region attributes 

			static bool						_signal;

			static std::string				_server_name;
			static std::string				_version;

			time_t							_launch_time;

			in_port_t						_port;
			std::string						_password;
			sockaddr_in						_s_addr;
			int								_serv_sfd;

			poll_vec						_poll; // Contient les sfd des client connectes ainsi que celui du serv(en premiere pos)
			Registry 						_reg;

			Bot *							_bot;

		#pragma endregion attributes
		//==========================================================//

		//================================= PRIVATE METHODS ========//
		#pragma region pmethods 

			void		push_new_poll(int fd, short events, short revents);
			size_t		count_clients();
			void		monitor_pollout(int fd, bool enable);

			void		accept_client();

			void		handle_readable(Client * cli);
			void		parse_cli_buff(Client * cli);

			void		handle_writable(Client * cli);
			
			void		ping_client(Client *cli);
			void		check_timeout();

		#pragma endregion pmethods 
		//==========================================================//

	public:
		//============================= CONST & DESTRUCTORS ========//
		#pragma region constructors

			Server();
			Server(in_port_t port, std::string password);
			~Server();

		#pragma endregion attributes
		//==========================================================//

		//========================================= METHODS ========//
		#pragma region methods

			static void			handle_signal(int sig);

			const std::string	get_str_lTime() const;

			void		init_serv();
			void		loop();

			void		append_client_sBuff(Client * cli, std::string str);
			void		send_to_channel(Channel * chan, Client * cli, std::string str);
			void		send_to_targetSet(TargetSet & trgSet, std::string str);

			void		close_poll(int fd);
			void		shutdown();

		#pragma endregion methods
		//==========================================================//

		//========================================= GETTERS ========//
		#pragma region getters 

			static const std::string &	get_server_name();
			static const std::string &	get_version();

			const in_port_t &			get_port() const;
			const std::string &			get_password() const;
			const sockaddr_in &			get_s_addr() const;
			const int &					get_serv_sfd() const;

			const Registry &			get_reg() const;
			Registry &					get_reg_ref();

		#pragma endregion getters
		//==========================================================//
	};

#endif // SERVER_HPP
