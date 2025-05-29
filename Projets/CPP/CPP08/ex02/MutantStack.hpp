/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:52 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/08 19:08:50y tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MUTANTSTACK_HPP
#define	MUTANTSTACK_HPP

// includes //
#include <iostream>
#include <stack>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
		public:
		// Default constructor
		MutantStack() : std::stack<T, Container>() { std::cout << "Empty MutantStack created\n"; }
		// Copy constructor
		MutantStack(MutantStack const & copy) : std::stack<T, Container>(copy) { std::cout << "Mutant stack copied\n"; }
		// Destructor
		~MutantStack() {std::cout << "Mutant stack deleted\n";}

		// Iterators //

		auto			begin( void )			{ return (std::stack<T, Container>::c.begin()); } // Ici c correspond au container sous-jacent de stack (protected)
		auto			rbegin( void )			{ return (std::stack<T, Container>::c.rbegin()); }
		const auto		cbegin( void ) const	{ return (std::stack<T, Container>::c.cbegin()); }
		const auto		crbegin( void ) const	{ return (std::stack<T, Container>::c.crbegin()); }
		auto			end( void )				{ return (std::stack<T, Container>::c.end()); }
		auto			rend( void )			{ return (std::stack<T, Container>::c.rend()); }
		const auto		cend( void ) const		{ return (std::stack<T, Container>::c.cend()); }
		const auto		crend( void ) const		{ return (std::stack<T, Container>::c.crend()); }

		// Operators //

		MutantStack&		operator = (const MutantStack& copy)
		{
			if (*this != copy)
				std::stack<Container>::operator=(copy);
			return (*this);
		}
};

#endif // MUTANTSTACK_HPP
