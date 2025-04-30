/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:09 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/30 20:28:50 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ARRAY_HPP
#define	ARRAY_HPP

// includes //
#include <iostream>

template<typename T>
class Array
{
	private:

		// attributes //
		T				*_parray;
		unsigned int	_length;

	public:
		// Default constructor
		Array();
		// Personnalized constructor
		Array(unsigned int n);
		// Copy constructor
		Array(const Array& copy);
		// Destructor
		~Array();

		// Methods //
		unsigned int	size( void ) const;

		// Operators //
		Array&			operator = (const Array& copy);
		T&				operator [] (unsigned int index);

};

#endif // ARRAY_HPP
