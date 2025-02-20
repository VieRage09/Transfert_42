#include "../genclass.hpp"

t_options	detect_options(char **tab)
{
	bool	attributes = false;
	bool	get_set = false;

	for(int	i = 2; tab[i]; i++)
	{
		std::string	str = tab[i];
		if (str[0] && str[0] == '-')
		{
			if (str[1] && str[2] && ((str[1] == 'a' && str[2] == 'g')
				|| (str[1] == 'g' && str[2] == 'a')))
			{
				get_set = true;
				attributes = true;
			}
			if (str[1] && str[1] == 'a')
				attributes = true;
			if (str[1] && str[1] == 'g') 
				get_set = true;	
		}
	}
	if (get_set && attributes)
		return (ALL);
	if (attributes)
		return (ASSIGN_ATTRIBUTES);
	return (NO_OPTION);
}	

int	main(int ac, char **av)
{
	if (ac < 2)
		return (std::cout << "Usage: ./genclass <ClassName> <options>\nOptions:\n\t-a \"<attributes>\" (coma separated): define your class attributes\n\t-g: automatically get getters and setters for the attributes\n", 1);

	t_options opt = detect_options(av);
	switch (opt)
	{
	case ALL:
		std::cout << "All options\n";
		break;
	case ASSIGN_ATTRIBUTES:
		std::cout << "Assignement of attributes\n";
		break;
	default:
		std::cout << "No option\n";
		break;
	}


	std::string		className = av[1];
	std::string		headerPath = className + ".hpp";
	std::string		cfilePath = className + ".cpp";
	std::ofstream	headFile(headerPath.c_str());
	std::ofstream	cppFile(cfilePath.c_str());

	if (!write_header_file(headFile, className, opt, av))
		return (std::cerr << "Error while writing header\n", 1);
	if (!write_cpp_file(cppFile, className, opt, av))
		return (std::cerr << "Error while writing cpp file\n", 1);

	return (0);
}