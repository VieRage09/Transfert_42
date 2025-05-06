/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:52 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/06 16:17:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MUTANTSTACK_HPP
#define	MUTANTSTACK_HPP

// includes //
#include <iostream>
#include <stack>
#include <deque>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack
{
	private:

		// attributes //

	public:
		// Default constructor
		MutantStack() : Container() {std::cout << "Mutant stack created\n";}
		// Copy constructor
		MutantStack(const MutantStack& copy) : Container(copy) {std::cout << "Mutant stack copied\n";}
		// Destructor
		~MutantStack() : ~Container() {std::cout << "Mutant stack deleted\n";}

		// Methods //
		Container::iterator &	begin() const
		{
			return (this->begin());
		}	

		Container::iterator &	end()
		{
			return (this->end());
		}	

		void MutantStack::printoui( void ) {std::cout << "oui\n";}
		// Container::iterator &	begin()
		// {

		// }	
		// Container::iterator &	begin()
		// {

		// }	

		// Operators //
		// MutantStack&		operator = (const MutantStack& copy)
		// {
		// 	if (*this != copy)
		// 	{

		// 	}
		// 	return (*this);
		// }

};

#endif // MUTANTSTACK_HPP
