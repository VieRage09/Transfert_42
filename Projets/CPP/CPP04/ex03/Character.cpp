/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:56:54 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/17 14:31:42 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

// STATIC INIT //


// CONSTRUCTORS & DESTRUCTORS //

Character::Character() : name("John")
{
	for(int i = 0; i < 4; i++)
		inventory[i]= NULL;
	for(int i = 0; i < 50; i++)
		floor[i] = NULL;
	std::cout << "Character default constructor called\n";
}

Character::Character(std::string const & name) : name(name)
{
	for(int i = 0; i < 4; i++)
		inventory[i]= NULL;
	for(int i = 0; i < 50; i++)
		floor[i] = NULL;
	std::cout << "Character special constructor called\n";
}

Character::Character(const Character& copy)	: Character(copy.name)
{
	for(int i = 0; i < 4; i++)
		if (copy.inventory[i])
			inventory[i] = copy.inventory[i]->clone();
	for(int i = 0; i < 50; i++)
		if (floor[i])
			floor[i] = copy.floor[i]->clone();
	std::cout << "Character copy constructor called\n";
}

Character::~Character()
{
	for(int i = 0; i < 4; i++)
		if (inventory[i])
			delete inventory[i];
	for(int i = 0; i < 50; i++)
		if (floor[i])
			delete floor[i];
	std::cout << "Character destructor called\n";
}

// METHODS //


void Character::equip(AMateria* m)
{
	int	i = 0;

	if (!m)
		return ;
	while (i < 4)
	{
		if (inventory[i] == NULL)
		{
			inventory[i] = m->clone();	// Faut il copier la materia ou pas ?	
			// inventory[i] = m;
			return ;
		}
		i++;
	}
	std::cout << "Inventory is full\n";
}

static bool	floor_is_full(AMateria * floor[])
{
	for (int i = 0; i < 50; i++)
		if (!floor[i])
			return (false);
	return (true);
}

void Character::unequip(int idx)
{
	if (idx > 3 || idx < 0 || !inventory[idx])
	{
		std::cout << "Wrong index for unequip\n";
		return ;
	}
	if (floor_is_full(floor))
	{
		std::cout << "Floor is full\n";
		return ;
	}
	if (inventory[idx])
	{
		int	i = 0;

		while (floor[i])
			i++;
		floor[i] = inventory[idx];
		inventory[idx] = NULL;
	}
}

void Character::use(int idx, ICharacter& target)
{
	if (idx > 3 || idx < 0)
	{
		std::cout << "Wrong index for use\n";
		return ;
	}
	if (inventory[idx])
		inventory[idx]->use(target);
	else
		std::cout << getName() << " has nothing to use at this index\n";
}

void	Character::print_inventory()
{
	std::cout << getName() << " inventory :\n";
	for(int i = 0; i < 4; i++)
	{
		std::cout << i << " = ";
		if (inventory[i])
			std::cout << inventory[i]->getType();
		std::cout << std::endl;
	}
}

void	Character::print_floor()
{
	std::cout << getName() << " floor :\n";
	for(int i = 0; i < 50; i++)
		if (floor[i])
			std::cout << i << " : " << floor[i]->getType() << std::endl;
}

// OPERATORS //

Character& Character::operator = (const Character& copy)
{
	if (this != &copy)
	{
		for(int i = 0; i < 4; i++)
		{
			if (inventory[i])
				delete inventory[i];
			if (copy.inventory[i])
				inventory[i] = copy.inventory[i]->clone();
			else
				inventory[i] = NULL;
		}
		for(int i = 0; i < 50; i++)
		{
				if (floor[i])
					delete floor[i];
				if (copy.floor[i])
					floor[i] = copy.floor[i]->clone();
				else
					floor[i] = NULL;
		}
		name = copy.name;
	}
	return (*this);
}

// GETTERS //

std::string const & Character::getName() const {return (this->name);}
