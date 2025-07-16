/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:45:36 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/26 23:48:08 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	DATA_HPP
#define	DATA_HPP

// includes //
#include <iostream>

struct Data
{
	// Default constructor
	Data(char c, int i, long l, float f, long double ld);
	// Destructor
	~Data();

	char		c;
	int			i;
	long		l;
	float		f;
	long double ld;
};

#endif // DATA_HPP
