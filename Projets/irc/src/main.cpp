#include "ircserv.hpp"

int	main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	// Check inputs + maybe changer atoi
	Server serv(atoi(av[1]), av[2]);
	
	try
	{
		signal(SIGINT, Server::handle_signal);
		signal(SIGQUIT, Server::handle_signal);
		serv.init_serv();
		serv.loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		serv.close_poll_sockets();
		return (1);
	}
	serv.close_poll_sockets();
	return (0);
}
	