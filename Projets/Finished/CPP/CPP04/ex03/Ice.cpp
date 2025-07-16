/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:40:18 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/08 22:20:12 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Ice::Ice() : AMateria("ice") {std::cout << "Ice constructor called\n";}

Ice::Ice(const Ice& copy) : AMateria(copy.type) {std::cout << "Ice copy constructor called\n";}

Ice::~Ice() {std::cout << "Ice destructor called\n";}

// METHODS //

AMateria* Ice::clone() const
{
	std::cout << "Cloning " << getType() << " materia\n";
	return (new Ice(*this));
}

void Ice::use(ICharacter& target) {std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";}

// OPERATORS //

Ice& Ice::operator = (const Ice& copy) // Sert a rien non plus
{
	if (this != &copy)
		type = copy.type;
	return (*this);
}
