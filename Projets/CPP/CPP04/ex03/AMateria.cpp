/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:10:13 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/06 18:53:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

// CONSTRUCTORS & DESTRUCTORS //

AMateria::AMateria() : type("") {std::cout << "AMateria default constructor called\n";}

AMateria::AMateria(std::string const & type): type(type) {std::cout << "AMateria specialised constructor called\n";}

AMateria::AMateria(const AMateria& copy): AMateria(copy.type) {std::cout << "AMateria copy constructor called\n";}

AMateria::~AMateria() {std::cout << "AMateria destructor called\n";}

// METHODS //

void AMateria::use(ICharacter& target) {std::cout << "*Blows a kiss at " << target.getName() << " *\n";}


// OPERATORS //

AMateria& AMateria::operator = (const AMateria& copy) // EUUUUUUh pas logique selon le sujet ??
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}

// GETTERS //

std::string const & AMateria::getType() const {return (this->type);}