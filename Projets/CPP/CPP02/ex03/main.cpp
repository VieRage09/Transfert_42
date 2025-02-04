/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:44:39 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/04 19:01:50 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

int main(void)
{
	Point	a;
	Point	b(2, 1);
	Point	c(3, 1);

	std::cout << a.get_x() << " " << a.get_y() << std::endl;
	std::cout << b.get_x() << " " << b.get_y() << std::endl;
	std::cout << c.get_x() << " " << c.get_y() << std::endl;
	c = b;
	std::cout << c.get_x() << " " << c.get_y() << std::endl;
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