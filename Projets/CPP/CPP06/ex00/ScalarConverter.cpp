/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:36:36 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/20 01:17:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// CONSTRUCTORS & DESTRUCTORS //

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

// METHODS //

void	ScalarConverter::print_conv_char(std::string str)
{
	char	converted;

	if (str.size() != 1)
		std::cerr << "WTF MA BOY\n";
	converted = str.front();
	std::cout	<< "char: " << converted
				<< "\nint: " << static_cast <int> (converted)
				<< "\nfloat: " << static_cast <float> (converted)
				<< "\ndouble: " << static_cast <double> (converted)
				<< std::endl;
}

void	ScalarConverter::print_conv_int(std::string str)
{
	int	converted;

	converted = atoi(str.c_str());
	std::cout	<< "char: " << static_cast <char> (converted)
				<< "\nint: " << converted
				<< "\nfloat: " << static_cast <float> (converted)
				<< "\ndouble: " << static_cast <double> (converted)
				<< std::endl;
}

void	ScalarConverter::print_conv_float(std::string str)
{
	float	converted;

	converted = atof(str.c_str());
	std::cout	<< "char: " << static_cast <char> (converted)
				<< "\nint: " << static_cast <int> (converted)
				<< "\nfloat: " << converted
				<< "\ndouble: " << static_cast <double> (converted)
				<< std::endl;
}

void	ScalarConverter::print_conv_double(std::string str) // Voir pour use cette methode dans les autres cas
{
	double	converted;
	std::stringstream ss;

	ss << str;
	if (ss >> converted)
	{
		std::cout	<< "char: " << static_cast <char> (converted)
					<< "\nint: " << static_cast <int> (converted)
					<< "\nfloat: " << static_cast <float> (converted)
					<< "\ndouble: " << converted
					<< std::endl;
	}
}

bool	ScalarConverter::check_nan_inf(std::string str)
{
	if (str.compare("nan") == 0)
		return (print_conv_double(str), true);
	if (str.compare("nanf") == 0)
		return (print_conv_float(str), true);
	if (str.compare("+inf") == 0)
		return (print_conv_double(str), true);
	if (str.compare("-inf") == 0)
		return (print_conv_double(str), true);
	if (str.compare("+inff") == 0)
		return (print_conv_float(str), true);
	if (str.compare("-inff") == 0)
		return (print_conv_float(str), true);
	return (false);
}

void		ScalarConverter::convert(const std::string str) // Selection a revoir
{
	char	c = 0;
	int		i = 0;
	float	f = 0;
	double	d = 0;

	if (!isprint(str.at(0))) // achanger
		return ; // Error message
	if (check_nan_inf(str))
		return ;
	if (str.find_first_not_of("-0123456789") != std::string::npos)	// str n'est pas un int
	{
		if (str.find_first_not_of("-0123456789.f") == std::string::npos)		// str est un float --> tester 0.42-f --> doit pas marcher + faire des tests de cons sur tout le reste
			print_conv_float(str);
		else if (str.find_first_not_of("-0123456789.") == std::string::npos)	// str est un double
			print_conv_double(str);
		else
			print_conv_char(str);												// str est un char 
	}
	else															// str est un int
		print_conv_int(str);
}