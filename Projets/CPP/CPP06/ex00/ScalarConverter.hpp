/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:13:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/26 23:19:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCALARCONVERTER_HPP
#define	SCALARCONVERTER_HPP

// includes //
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>

class ScalarConverter
{
	private:
		// Default constructor
		ScalarConverter();
	public:
		// Destructor
		~ScalarConverter();

		// Methods //
		static void		convert(const std::string str);

};

#endif // SCALARCONVERTER_HPP
