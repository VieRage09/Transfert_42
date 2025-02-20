#include "../genclass.hpp"

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
	if (type[type.size() - 1] == ',')
		type.erase(type.size() - 1);
	return (type);
}

std::string	get_name(std::string& str)
{
	std::string	name;

	name = str.substr(str.find_first_not_of(' '));
	name = name.substr(name.find_first_of(' ') + 1);
	name = name.substr(name.find_first_not_of(' '));
	if (name[0] == '&' || name[0] == '*')
		name.erase(0, 1);
	if (name.find_first_of(',') != std::string::npos)
		name.erase(name.find_first_of(','));
	// if (name[name.size() - 1] == ',')
	// 	name.erase(name.size() - 1);
	return (name);
}

bool	is_pointer(std::string& type)
{
	if (type[type.size() - 1] == '*')
		return (true);
	return (false);
}