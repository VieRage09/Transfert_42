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

		// Iterators //

		auto			begin( void ) {return (stk.begin());}
		auto			rbegin( void ) {return (stk.rbegin());}
		const auto		cbegin( void ) const {return (stk.cbegin());}
		const auto		crbegin( void ) const {return (stk.crbegin());}
		auto			end( void ) {return (stk.end());}
		auto			rend( void ) {return (stk.rend());}
		const auto		cend( void ) const {return (stk.cend());}
		const auto		crend( void ) const {return (stk.crend());}

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

// Non-member functions overloads //

template <typename T, typename Container>
bool	operator == (MutantStack<T, Container> & lhs, MutantStack<T, Container> & rhs) {return (lhs.get_stk() == rhs.get_stk());}
template <typename T, typename Container>
bool	operator != (MutantStack<T, Container> & lhs, MutantStack<T, Container> & rhs) {return (lhs.get_stk() != rhs.get_stk());}
template <typename T, typename Container>
bool	operator > (MutantStack<T, Container> & lhs, MutantStack<T, Container> & rhs) {return (lhs.get_stk() > rhs.get_stk());}
template <typename T, typename Container>
bool	operator >= (MutantStack<T, Container> & lhs, MutantStack<T, Container> & rhs) {return (lhs.get_stk() >= rhs.get_stk());}
template <typename T, typename Container>
bool	operator < (MutantStack<T, Container> & lhs, MutantStack<T, Container> & rhs) {return (lhs.get_stk() < rhs.get_stk());}
template <typename T, typename Container>
bool	operator <= (MutantStack<T, Container> & lhs, MutantStack<T, Container> & rhs) {return (lhs.get_stk() <= rhs.get_stk());}


template <typename T, typename Container>
void		swap(MutantStack<T, Container> & a, MutantStack<T, Container> & b) noexcept {a.swap(b.get_stk());}

#endif // MUTANTSTACK_HPP
