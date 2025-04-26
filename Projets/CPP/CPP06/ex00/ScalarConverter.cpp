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

template <typename T>
void		display_converted(T val, char overflow)
{
	if (std::isnan(static_cast <double> (val)) || std::isinf(static_cast <double> (val)))
		std::cout	<< "char: impossible" << std::endl
					<< "int: impossible" << std::endl;
	else
	{
		if (isprint(static_cast <char> (val)) && overflow == 0)
			std::cout	<< "char: '" << static_cast <char> (val) << "'" << std::endl;
		else
			std::cout	<< "char: Non displayable" << std::endl;
		if (overflow == 'i' || overflow == 'f')
			std::cout	<< "int: " << "overflow" << std::endl;
		else
			std::cout	<< "int: " << static_cast <int> (val) << std::endl;
	}
	if (overflow == 'f')
	{
		std::cout 	<< "float: " << "overflow" << std::endl
					<< "double: " << "overflow" << std::endl;
	}
	else
	{
		std::cout 	<< "float: " << static_cast <float> (val) << "f" << std::endl
					<< "double: " << static_cast <double> (val) << std::endl;
	}

}

void		conv_char_str(std::string str)
{
	char	c;

	c = str.front();
	display_converted(c, 0);
}

void		conv_int_str(std::string str)
{
	long long	ll;

	try
	{
		ll = std::stoll(str, NULL, 10);
		if (ll > std::numeric_limits<int>::max() || ll < std::numeric_limits<int>::min())
			display_converted(ll, 'i');
		else
			display_converted(ll, 0);
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << "Error: long long overflow" << std::endl;
		int	i = 0;
		display_converted(i, 'f');
		return ;
	}
	catch(const std::exception& e) // Voir si c'est necessaire cf ^^^
	{
		std::cerr << "Error: " << e.what() << " failed" << std::endl;
		return ;
	}
}

void	conv_float_str(std::string str)
{
	long double ld;

	try
	{
		ld = std::stold(str, NULL);
		if (ld > std::numeric_limits<float>::max() || ld < std::numeric_limits<float>::min())
			display_converted(ld, 'f');
		else if (ld > std::numeric_limits<int>::max() || ld < std::numeric_limits<int>::min())
			display_converted(ld, 'i');
		else
			display_converted(ld, 0);
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << "Error: long double overflow" << std::endl;
		return ;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "failed" << std::endl;
		return ;
	}
}

void	conv_double_str(std::string str)
{
	long double ld;

	try
	{
		ld = std::stold(str, NULL);
		if (ld > std::numeric_limits<double>::max() || ld < std::numeric_limits<double>::min())
			display_converted(ld, 'f');
		else if (ld > std::numeric_limits<int>::max() || ld < std::numeric_limits<int>::min())
			display_converted(ld, 'i');
		else
			display_converted(ld, 0);
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << "Error: long double overflow" << std::endl;
		return ;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << "failed" << std::endl;
		return ;
	}
}



void		ScalarConverter::convert(const std::string str) // est ce que 4f est un float ? Si oui probleme
{
	if (str.empty())
	{
		printf("Error: empty string\n");
		return ;
	}
	if (str_is_char(str))
		conv_char_str(str);
	else if (str_is_int(str))
		conv_int_str(str);
	else if (str_is_float(str))
		conv_float_str(str);
	else if (str_is_double(str))
		conv_double_str(str);
	else
		std::cerr << "Wrong input: not a literal\n";
}