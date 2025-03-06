#include "Character.hpp"


// CONSTRUCTORS & DESTRUCTORS //

Character::Character() : ICharacter(), name("John")
{

	std::cout << "Character default constructor called\n";
}

Character::Character(std::string const & name) : ICharacter(), name(name)
{

}

Character::Character(const Character& copy)
{

	std::cout << "Character copy constructor called\n";
}

Character::~Character()
{
	std::cout << "Character destructor called\n";
}

// METHODS //

std::string const & Character::getName() const {return (this->name);}

void Character::equip(AMateria* m)
{

}

void Character::unequip(int idx)
{

}

void Character::use(int idx, ICharacter& target)
{

}

// OPERATORS //

Character& Character::operator = (const Character& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}
