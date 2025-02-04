/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:46:56 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/04 19:09:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
	private:
		Fixed const	x;
		Fixed const	y;

	public:
		Point();
		Point(float const x, float const y);
		Point(const Point& copy);
 	   ~Point();
	   
		const Fixed&	get_x( void ) const;
		const Fixed&	get_y( void ) const;
	   
	   Point&	operator = (const Point& copy);
	   bool		operator == (const Point& copy) const;
};

#endif // POINT_HPP
