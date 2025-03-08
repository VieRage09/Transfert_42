/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:40:05 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/08 22:19:42 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Cure::Cure(): AMateria("cure") {std::cout << "Cure constructor called\n";}

Cure::Cure(const Cure& copy) : AMateria(copy.type) {std::cout << "Cure copy constructor called\n";}

Cure::~Cure() {std::cout << "Cure destructor called\n";}

// METHODS //

AMateria* Cure::clone() const
{
	std::cout << "Cloning " << getType() << " materia\n";
	return (new Cure(*this));
}

void Cure::use(ICharacter& target) {std::cout << "* heals " << target.getName() << "\'s wounds *\n";}

// OPERATORS //

Cure& Cure::operator = (const Cure& copy) // Sert a rien
{
	if (this != &copy)
		type = copy.type;
	return (*this);
}
