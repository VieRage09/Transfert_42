#include "genclass.hpp"

std::string	capitalize(std::string& str)
{
	std::string	ret = str;

	for(unsigned int i = 0; i < str.size(); i++)
		ret[i] = std::toupper(str[i]);
	return (ret);
}

std::string	get_attributes(char **tab)
{
	if (tab[2])
	{
		for(int i = 2; tab[i]; i++)
		{
			std::string	str = tab[i];
			if (str.find("-", 0) == std::string::npos)
				return (str);
		}
	}
	return ("");
}

std::string	get_type(std::string& str)
{
	std::string	type;

	type = str.substr(0, str.find_first_of(' '));
	if (str.find_first_of('*') != std::string::npos)
		type += '*';
	if (str.find_first_of('&') != std::string::npos)
		type += '&';
	return (type);
}

std::string	get_name(std::string& str)
{
	std::string	name;

	std::cout << "Str received : " << str << std::endl;

	name = str.substr(str.find_first_of(' ') + 1);
	if (name[0] == '&' || name[0] == '*')
		name.erase(0, 1);
	std::cout << "name = " << name << std::endl;
	return (name);
}