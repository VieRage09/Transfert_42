/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:46:56 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/03 20:54:44 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
	private:
		Fixed	x;
		Fixed	y;

	public:
		Point();
		Point(const Fixed& x, const Fixed& y);
 	   ~Point();

};

#endif // POINT_HPP
