/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:53:44 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 18:50:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

// Used to determine if p belongs to (ab) line
// Returns true if p does belong to [ab] and also true if p doesn't belong to [ab] but does to (ab)
static bool	pointBelongsToLine(const Point& a, const Point& b, const Point& p)
{
	if (a.get_x() == b.get_x())
	{
		if (p.get_x() == a.get_x())
				return (true);
		return (false);
	}
	if (a.get_y() == b.get_y())
	{
		if (p.get_y() == a.get_y())
				return (true);
		return (false);
	}

	Fixed	coef((b.get_y() - a.get_y()) / (b.get_x() - a.get_x()));
	Fixed	o_origin(a.get_y() - a.get_x() * coef);
	
	if (p.get_y() == (coef * p.get_x() + o_origin))
		return (true);
	return (false);
}

static	Fixed	area(const Point& a, const Point& b, const Point& c)
{
	Fixed	area =	( a.get_x() * (b.get_y() - c.get_y())
					+ b.get_x() * (c.get_y() - a.get_y())
					+ c.get_x() * (a.get_y() - b.get_y())) / 2;
	if (area < Fixed(0))
		area = area * Fixed(-1);
	return (area);
}

static bool	compare_area_error_margin(Fixed area0, Fixed area1, Fixed area2, Fixed area3)
{
	Fixed total = area1 + area2 + area3;
	Fixed	inf = --total;
	Fixed	supp = ++total;

	if (area0 >= --total && area0 <= ++total)
		return true;
	return (false);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	// Checks if point is one of the verticies of the triangle
	if (point == a || point == b || point == c)
	{
		std::cout << "ERROR: The point p is equal to point";
		if (point == a)
			std::cout << " a\n";
		if (point == b)
			std::cout << " b\n";
		if (point == c)
			std::cout << " c\n";
		return (false);	
	}
	// Checks if point belongs to the sides of the triangle
	if (pointBelongsToLine(a, b, point) || pointBelongsToLine(b, c, point) || pointBelongsToLine(c, a, point))
	{
		std::cout << "ERROR: The point p belongs to one of the lines formed by the triangles sides\n";
		return (false);
	}
	std::cout << "Calculating areas\n";
	return (compare_area_error_margin(area(a, b, c), area(point, a, b), area(point, b, c), area(point, c, a)));
}
