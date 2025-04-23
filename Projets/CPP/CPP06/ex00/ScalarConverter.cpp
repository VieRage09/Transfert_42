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

bool	has_lone_point(std::string	str)
{
	return (str.find('.') != std::string::npos && str.find('.') == str.rfind('.'));
}


bool	str_is_char(std::string str)
{

}
bool	str_is_int(std::string str)
{
	if (str.at(0) == '-' || str.at(0) == '+') // Exerese du prefix s'il y en a pour eviter a avoir a l'inclure dans les checks de char suivants
		str = str.substr(1, str.size());
	return (str.find_first_not_of("0123456789") == std::string::npos);
}
bool	str_is_float(std::string str)
{
	if (str.at(0) == '-' || str.at(0) == '+') // Exerese du prefix s'il y en a pour eviter a avoir a l'inclure dans les checks de char suivants
		str = str.substr(1, str.size());
	if (str.compare("nanf") == 0 || str.compare("inff") == 0)
		return (true);
	return (has_lone_point(str) && str.find_first_not_of("0123456789.f") == std::string::npos && str.back() == 'f') // A modifier pour renvoyer false si 12f4
}
bool	str_is_double(std::string str)
{
	if (str.at(0) == '-')
		str = str.substr(1, str.size());
	if (str.compare("nan") == 0 || str.compare("inf") == 0)
		return (true);
	return (has_lone_point(str) && str.find_first_not_of("0123456789.") == std::string::npos)
}

void		ScalarConverter::convert(const std::string str)
{
	
	
}