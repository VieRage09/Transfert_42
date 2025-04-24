/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:13:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/24 19:20:03 by tlebon           ###   ########.fr       */
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
#include <iomanip>

class ScalarConverter
{
	private:
		// Default constructor
		ScalarConverter();
		void	display_values(void *addr, char type);
	public:
		// Destructor
		~ScalarConverter();

		// Methods //
		static void		convert(const std::string str);

};

#endif // SCALARCONVERTER_HPP
