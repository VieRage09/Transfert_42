/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:44:39 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/28 22:25:17 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <limits.h>

int main()
{
	Fixed zero;
	Fixed a(2);
	Fixed b(5);
	Fixed c = a + b;
	Fixed d = a - b;
	Fixed e = a * b;
	Fixed f = b / d;
	Fixed g = zero * a / b;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl;
	std::cout << g << std::endl;
	if (a < b)
		std::cout << "a < b" << std::endl;
	if (a > f)
		std::cout << "a > f" << std::endl;
	if (g <= a)
		std::cout << "g <= a" << std::endl;
	if (b >= a)
		std::cout << "b >= a" << std::endl;
	if (g == zero)
		std::cout << "g == zero" << std::endl;
	if (g != c)
		std::cout << "g != c" << std::endl;
}

// int main(void)
// {
// 	Fixed a;
// 	Fixed const b(Fixed(5.05f) * Fixed(2));
// 	std::cout << a << std::endl;
// 	std::cout << ++a << std::endl;
// 	std::cout << a << std::endl;
// 	std::cout << a++ << std::endl;
// 	std::cout << a << std::endl;
// 	std::cout << b << std::endl;
// 	std::cout << Fixed::max(a, b) << std::endl;
// 	return 0;
// }