/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:13:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/20 01:14:20 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCALARCONVERTER_HPP
#define	SCALARCONVERTER_HPP

// includes //
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <sstream>

class ScalarConverter
{
	private:
		// Default constructor
		ScalarConverter();
		static bool	check_nan_inf(std::string str);
		static void print_conv_char(std::string str);
		static void print_conv_int(std::string str);
		static void print_conv_float(std::string str);
		static void print_conv_double(std::string str);
	public:
		// Destructor
		~ScalarConverter();

		// Methods //
		static void		convert(const std::string str);

};

#endif // SCALARCONVERTER_HPP
