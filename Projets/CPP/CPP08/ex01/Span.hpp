/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:29:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/05 19:43:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SPAN_HPP
#define	SPAN_HPP

// includes //
#include <iostream>
#include <vector>
#include <algorithm>

class Span
{
	private:

		// attributes //
		unsigned			int _N;
		std::vector<int>	_vec;

	public:
		// Personnalized constructor
		Span(unsigned int N);
		// Copy constructor
		Span(const Span& copy);
		// Destructor
		~Span();

		// Custom methods //
		void			display_span( void ) const; 
		void			add_alot_of_numbers(bool random);

		// Methods //
		void			addNumber(int n);
		void			addRange(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last);
		unsigned int	shortestSpan() const;
		unsigned int	longestSpan() const;
		


		// Operators //
		Span&			operator = (const Span& copy);

		// Getters //
		const unsigned&		get_N() const;

};

#endif // SPAN_HPP
