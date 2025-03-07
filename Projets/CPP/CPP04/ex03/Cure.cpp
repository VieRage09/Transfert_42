/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:40:05 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/07 16:40:06 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Cure::Cure(): AMateria("cure") {std::cout << "Cure constructor called\n";}

Cure::Cure(const Cure& copy) {}

Cure::~Cure() {std::cout << "Cure destructor called\n";}

// METHODS //

AMateria* Cure::clone() const
{
	AMateria *	clone = new Cure(*this); // nothrow / try catch pour verifier l'alloc ?
	return (clone);
}

void Cure::use(ICharacter& target) {std::cout << "* heals " << target.getName() << "\'s wounds *";}

// OPERATORS //

Cure& Cure::operator = (const Cure& copy) // Jcp 
{
	if (this != &copy)
	{
		
	}
	return (*this);
}
