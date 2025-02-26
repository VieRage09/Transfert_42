/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:53:44 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 20:41:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <iostream>

// Used to determine if p belongs to [ab] segment
// Returns true if p does belong to [ab]
static bool	pointBelongsToSegment(const Point& a, const Point& b, const Point& p)
{
	if (a.get_x() == b.get_x())
	{
		if (p.get_x() == a.get_x())
		{
			if (p.get_y() > Fixed::min(a.get_y(), b.get_y())
				&& p.get_y() < Fixed::max(a.get_y(), b.get_y()))
				return (true);
		}
		return (false);
	}
	if (a.get_y() == b.get_y())
	{
		if (p.get_y() == a.get_y())
		{
			if (p.get_x() > Fixed::min(a.get_x(), b.get_x())
				&& p.get_x() < Fixed::max(a.get_x(), b.get_x()))	
				return (true);
		}
		return (false);
	}
	Fixed	coef((b.get_y() - a.get_y()) / (b.get_x() - a.get_x()));
	Fixed	o_origin(a.get_y() - a.get_x() * coef);
	
	// std::cout << "Equation found for " << a << b << " y = " << coef << " * x " << " + " << o_origin << std::endl;
	if (p.get_y() == (coef * p.get_x() + o_origin) && (p.get_x() >= Fixed::min(a.get_x(), b.get_x()) && p.get_x() <= Fixed::max(a.get_x(), b.get_x())))
		return (true);
	return (false);
}
// y = ax + b
// b = y - ax
// y = coef * x + o_origin

// static bool	pointBelongsToLine(const Point& a, const Point& b, const Point& p)
// {
// 	Fixed	minus(-1);
// 	Fixed	xDelta(b.get_x() - a.get_x());
// 	Fixed	yDelta(b.get_y() - a.get_y());
// 	Fixed	m = yDelta / xDelta; 
// 	Fixed	h(minus * m * a.get_x() + a.get_y());

// 	if (xDelta == 0)
// 	{	
// 		if (a.get_x() == p.get_x() && p.get_y() <= Fixed::max(a.get_y(), b.get_y()) // Erreur est peut etre la 
// 				&& p.get_y() >= Fixed::min(a.get_y(), b.get_y()))
// 			return (true);
// 		return (false);
// 	}
// 	// std::cout << "Equation found for curve between a" << a << " and b" << b << ": " << "m = " << m << ", h = " << h << std::endl;
// 	if (p.get_y() == m * p.get_x() + h)
// 	{
// 		// std::cout << "p" << p << " belongs to line (ab)\n";
// 		if (p.get_x() <= Fixed::max(a.get_x(), b.get_x()) && p.get_x() >= Fixed::min(a.get_x(), b.get_x())
// 			&& p.get_y() <= Fixed::max(a.get_y(), b.get_y()) && p.get_y() >= Fixed::min(a.get_y(), b.get_y()))
// 				return (true);
// 	}
// 	return (false);
// }

static	Fixed	area(const Point& a, const Point& b, const Point& c)
{
	// double	ab = sqrt( pow( b.get_x().toFloat() - a.get_x().toFloat(), 2 ) + pow( b.get_y().toFloat() - a.get_y().toFloat(), 2 ));
	// double	ac = sqrt( pow( c.get_x().toFloat() - a.get_x().toFloat(), 2 ) + pow( c.get_y().toFloat() - a.get_y().toFloat(), 2 ));
	// double	bc = sqrt( pow( c.get_x().toFloat() - b.get_x().toFloat(), 2 ) + pow( c.get_y().toFloat() - b.get_y().toFloat(), 2 ));
	// float	heron = (float) sqrt( (ab + bc + ac) * (-ab + bc + ac) * (ab - bc + ac) * (ab + bc - ac) ) / 4;

	// return (Fixed(heron));
	Fixed	area =	( a.get_x() * (b.get_y() - c.get_y())
					+ b.get_x() * (c.get_y() - a.get_y())
					+ c.get_x() * (a.get_y() - b.get_y())) / 2;
	return (area);
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
	if (pointBelongsToSegment(a, b, point) || pointBelongsToSegment(b, c, point) || pointBelongsToSegment(c, a, point))
	{
		std::cout << "ERROR: The point p belongs to one of the sides of the triangle abc\n";
		return (false);
	}
	std::cout << "Calculating areas\n";
	return (area(a, b, c) == area(a, b, point) + area(a, c, point) + area(b, c,  point));
}
