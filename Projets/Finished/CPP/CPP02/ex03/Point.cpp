/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:46:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 18:26:30 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// Constructeurs & Destructeur /////////////////////////////////////////////////

Point::Point(): x(Fixed(0)), y(Fixed(0)) {}

Point::Point(float const x, float const y): x(x), y(y) {}

Point::Point(const Point& copy): x(copy.x), y(copy.y) {}

Point::~Point() {}

////////////////////////////////////////////////////////////////////////////////

// Methods /////////////////////////////////////////////////////////////////////
const Fixed&	Point::get_x( void ) const {return (x);}

const Fixed&	Point::get_y( void ) const {return (y);}

////////////////////////////////////////////////////////////////////////////////

// Operator overload ///////////////////////////////////////////////////////////
Point&	Point::operator = (const Point& copy)
{
	if (this != &copy)
	{
		(Fixed) this->x = copy.x;
		(Fixed) this->y = copy.y;
	}
	return (*this);
}

bool		Point::operator == (const Point& other) const
{
	if (x == other.get_x() && y == other.get_y())
		return (true);
	return (false);
}
////////////////////////////////////////////////////////////////////////////////

std::ostream&	operator << (std::ostream& os, const Point& p)
{
	os << "(" << p.get_x() << " ; " << p.get_y() << ")";
	return (os);
}