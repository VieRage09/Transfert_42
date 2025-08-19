#include "colonist.hpp"

int	main(int ac, char **av)
{
	// Check map format
	//Proteger
	std::string		str;

	try
	{
		Map	map(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}

