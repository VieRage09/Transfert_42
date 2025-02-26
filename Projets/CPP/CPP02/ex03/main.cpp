/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:44:39 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 16:49:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool	bsp(Point const a, Point const b, Point const c, Point const point);

int main(int ac, char ** av)
{
	Point	a(0, 0);
	Point	b(3, 0);
	Point	c(0, 3);
	if (ac < 3 || ac > 3)
	{
		std::cout << "only 2 numerical args accepted\n";
		return 1;
	}
	float	x1 = atof(av[1]);
	float	x2 = atof(av[2]);
	std::cout << "Point tried ("<< x1 << " ; " << x2 << ")\n";
	Point	p( (float) atof(av[1]), (float) atof(av[2]));

	bool x = bsp(a, b, c, p);
	if (x == true)
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
}
