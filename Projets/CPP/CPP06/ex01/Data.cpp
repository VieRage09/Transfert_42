/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:45:38 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/27 14:38:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Data::Data(char c, int i, long l, float f, long double ld) : c(c), i(i), l(l), f(f), ld(ld)
{
	std::cout << "Struct Data created\n";
}

Data::~Data() {std::cout << "Struct Data destroyed\n";}
