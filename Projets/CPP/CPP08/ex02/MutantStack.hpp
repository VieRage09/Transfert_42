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

		auto			begin( void ) {return (std::stack<T, Container>::c.begin());} <-- Juste la la 
		// auto			rbegin( void ) {return (stk.rbegin());}
		// const auto		cbegin( void ) const {return (stk.cbegin());}
		// const auto		crbegin( void ) const {return (stk.crbegin());}
		// auto			end( void ) {return (stk.end());}
		// auto			rend( void ) {return (stk.rend());}
		// const auto		cend( void ) const {return (stk.cend());}
		// const auto		crend( void ) const {return (stk.crend());}

		// Operators //

		MutantStack&		operator = (const MutantStack& copy)
		{
			if (*this != copy)
				std::stack<Container>::operator=(copy);
			return (*this);
		}
};

#endif // MUTANTSTACK_HPP
