/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:44:39 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/03 20:43:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;
	return 0;
}

// int	main()
// {
// 	Fixed	a(2);
// 	Fixed	b(3);
// 	Fixed	c = a + b;
// 	Fixed	d = a - b;
// 	Fixed	e = a * b;
// 	Fixed	f = b / d;



// 	if (a != b)
// 		std::cout << "oui" << std::endl;

// 	std::cout << a << std::endl;
// 	std::cout << b << std::endl;
// 	std::cout << c << std::endl;
// 	std::cout << d << std::endl;
// 	std::cout << e << std::endl;
// 	std::cout << f << std::endl;
// }