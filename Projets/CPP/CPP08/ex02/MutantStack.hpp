/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:52 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/08 18:54:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MUTANTSTACK_HPP
#define	MUTANTSTACK_HPP

// includes //
#include <iostream>
#include <deque>

template <typename T, typename Container = std::deque<T> >
class MutantStack
{
	private:
		// attributes //
		Container stk;

	public:
		// Default constructor
		MutantStack() : stk(Container()) {std::cout << "Empty MutantStack created\n";}
		// Parametric constructor
		MutantStack(size_t size, T init_value) : stk(Container(size, init_value))
		{
			std::cout	<< "MutantStack of size " << size
						<< " created with initialization value of " << init_value
						<< std::endl;
		}
		// Copy constructor
		MutantStack(const MutantStack& copy) : stk(Container(copy)) {std::cout << "Mutant stack copied\n";}
		// Destructor
		~MutantStack() {std::cout << "Mutant stack deleted\n";}

		// Methods //

		bool		empty( void ) const {return (stk.empty());}
		auto		size( void ) const {return (stk.size());}
		T &			top( void ) {return (stk.back());}
		void		push(const T & value) {stk.push_back(value);}
		template <typename... Args>
		void		emplace(Args&&... args) {stk.emplace_back(args...);}
		void		pop( void ) {stk.pop_back();}
		void		swap(MutantStack<T, Container> & other) noexcept {stk.swap(other.get_stk());}

		// Operators //

		// MutantStack&		operator = (const MutantStack& copy)
		// {
		// 	if (*this != copy)
		// 	{

		// 	}
		// 	return (*this);
		// }

		// Getters //
		auto &	get_stk( void ) {return (stk);}

};

#endif // MUTANTSTACK_HPP
