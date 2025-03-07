/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:56:54 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/07 19:05:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

// STATIC INIT //


// CONSTRUCTORS & DESTRUCTORS //

Character::Character() : name("John")
{
	for(int i = 0; i < 4; i++)
		inventory[i]= NULL;
	std::cout << "Character default constructor called\n";
}

Character::Character(std::string const & name) : name(name)
{
	for(int i = 0; i < 4; i++)
		inventory[i]= NULL;
	std::cout << "Character special constructor called\n";
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
	int	i = 0;

	if (!m)
		return ;
	while (i < 4)
	{
		if (inventory[i] == NULL)
		{
			inventory[i] = m;	// Faut il copier la materia ou pas ?	
			return ;
		}
		i++;
	}
	std::cout << "Inventory is full\n";
}

void Character::unequip(int idx)
{
	if (idx > 3 || idx < 0)
	{
		std::cout << "Wrong index for unequip\n";
		return ;
	}
	inventory[idx] = NULL; // Comment recup pour la mettre sur le sol ?
}

void Character::use(int idx, ICharacter& target)
{
	if (idx > 3 || idx < 0)
	{
		std::cout << "Wrong index for use\n";
		return ;
	}
}

// OPERATORS //

Character& Character::operator = (const Character& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}
