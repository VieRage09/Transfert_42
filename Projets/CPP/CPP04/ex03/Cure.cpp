#include "Cure.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Cure::Cure(): AMateria("cure") {std::cout << "Cure constr called\n";}

Cure::Cure(const Cure& copy) {}

Cure::~Cure() {std::cout << "Cure dest called\n";}

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
