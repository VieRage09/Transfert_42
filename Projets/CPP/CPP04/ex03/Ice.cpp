/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:40:18 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/07 16:40:28 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Ice::Ice() : AMateria("ice") {std::cout << "Ice constructor called\n";}

Ice::Ice(const Ice& copy) {}

Ice::~Ice() {std::cout << "Ice destructor called\n";}

// METHODS //

AMateria* Ice::clone() const
{
	AMateria *	clone = new Ice(*this);
	return (clone);
}

void Ice::use(ICharacter& target) {std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";}

// OPERATORS //

Ice& Ice::operator = (const Ice& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}
