#include "ircserv.hpp"

int	main(int ac, char **av)
{
	// Check inputs
	Server serv(std::stoi(av[1]), av[2]);
	
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
		return (1);
	}
}
	