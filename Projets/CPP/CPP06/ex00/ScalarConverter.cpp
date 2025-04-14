/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:36:36 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/14 18:18:20 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// CONSTRUCTORS & DESTRUCTORS //

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

// METHODS //

void		ScalarConverter::convert(char *str)
{
	char	c = str[0];
	int		*i = static_cast<int*>(str);
	float	f = static_cast<float>(i);
	double	d = static_cast<double>(f);
	// Chars
	std::cout << c << std::endl;
	std::cout << i << std::endl;
	std::cout << f << std::endl;
	std::cout << d << std::endl;
}
