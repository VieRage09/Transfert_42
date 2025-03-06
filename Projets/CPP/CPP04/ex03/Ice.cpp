#include "Ice.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Ice::Ice() : AMateria("ice") {std::cout << "Ice constr called\n";}

Ice::Ice(const Ice& copy) {}

Ice::~Ice() {std::cout << "Ice dest called\n";}

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
