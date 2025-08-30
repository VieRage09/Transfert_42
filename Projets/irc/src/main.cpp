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
		std::cerr << "[Exception thown]: "<< e.what() << '\n';
		serv.close_all_poll();
		return (1);
	}
	serv.close_all_poll();
	std::cout << GREEN << "Server stopped with success" << RESET << std::endl;
	return (0);
}
	