/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:53:44 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/04 19:29:16 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static bool	pointBelongsToLine(Point const a, Point const b, Point const p)
{
	Fixed	minus(-1);
	Fixed	m((b.get_y() - a.get_y()) / (b.get_x() - a.get_x())); 
	Fixed	h(minus * m * a.get_x() + a.get_y());
	if (p.get_y() == m * p.get_x() + h)
		return (true);
	return (false);
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	// Checks if point is one of the verticies of the triangle
	if (point == a || point == b || point == c)
		return (false);	
	// Checks if point belongs to the sides of the triangle
	if (pointBelongsToLine(a, b, point) || pointBelongsToLine(b, c, point) || pointBelongsToLine(c, a, point))
		return (false);
}
