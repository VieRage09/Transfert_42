/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:36:36 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 22:20:12y tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// CONSTRUCTORS & DESTRUCTORS //

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

// METHODS //

bool	has_lone_point(std::string str)
{
	return (str.find('.') != std::string::npos && str.find('.') == str.rfind('.'));
}

bool	str_is_char(std::string str)
{
	return (str.size() == 1 && str.find_first_of("0123456789") == std::string::npos);
}
bool	str_is_int(std::string str) // Gerer les overflows ici ?
{
	if (str.front() == '-' || str.front() == '+') // Exerese du prefix s'il y en a pour eviter a avoir a l'inclure dans les checks de char suivants
		str = str.substr(1, str.size());
	return (str.find_first_not_of("0123456789") == std::string::npos);
}
bool	str_is_float(std::string str)
{
	if (str.compare("nanf") == 0)
		return (true);
	if (str.front() == '-' || str.front() == '+') // Exerese du prefix s'il y en a pour eviter a avoir a l'inclure dans les checks de char suivants
		str = str.substr(1, str.size());
	if (str.compare("inff") == 0)
		return (true);
	if (str.back() == 'f')
		str = str.substr(0, str.size() - 1);
	else
		return (false);
	return (has_lone_point(str) && str.find_first_of("0123456879") != std::string::npos && str.find_first_not_of("0123456789.") == std::string::npos);
}
bool	str_is_double(std::string str)
{
	if (str.compare("nan") == 0)
		return (true);
	if (str.front() == '-' || str.front() == '+')
		str = str.substr(1, str.size());
	if  (str.compare("inf") == 0)
		return (true);
	return (has_lone_point(str) && str.find_first_of("0123456879") != std::string::npos && str.find_first_not_of("0123456789.") == std::string::npos);
}

void	display_char(void *addr, char type)
{
	std::cout	<< "char: ";
	if (type == 'c')
		std::cout << ""
}

void	display_int(void *addr, char type)
{

}

void	display_float(void *addr, char type)
{

}

void	display_double(void *addr, char type)
{

}

void	ScalarConverter::display_values(void *addr, char type)
{
	display_char(addr, type);
	display_int(addr, type);
	display_float(addr, type);
	display_double(addr, type);
}

void		ScalarConverter::convert(const std::string str) // est ce que 4f est un float ? Si oui probleme
{
	if (str.empty())
	{
		printf("Error: empty string\n");
		return ;
	}
	if (str_is_char(str))
	{
		char	c = str.front();
		printf("You entered a char: %c\n", c);
		
	}
	if (str_is_int(str))
	{
		try
		{
			int		i = std::stoi(str, NULL, 10);
			printf("You entered an int: %i\n", i);
		}
		catch(const std::exception& e) // Comment recup la bonne exception ? 
		{
			std::cerr <<"Error: " << e.what() << " failed" << std::endl;
		}
	}
	if (str_is_float(str))
	{
		float	f = std::stof(str, NULL);
		printf("You entered a float: %f\n", f);

	}
	if (str_is_double(str))
	{
		double	d = std::stod(str, NULL);
		printf("You entered a double %f\n", d);

	}
}