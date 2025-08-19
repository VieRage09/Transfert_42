#include "Server.hpp"

int	main(int ac, char **av)
{
	// Check inputs
	Server serv(std::stoi(av[1]), av[2]);
	
	try
	{
		serv.init_serv();
		serv.loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
}
	