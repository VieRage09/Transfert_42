/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:06:52 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/24 01:57:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

// CONSTRUCTORS & DESTRUCTORS //
ScavTrap::ScavTrap(): ClapTrap()
{
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << "ScavTrap " << name << " has been created\n";
}

ScavTrap::ScavTrap(const std::string str): ClapTrap(str)
{
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 20;
	std::cout << "ScavTrap " << name << " is born\n";
}

ScavTrap::ScavTrap(const ScavTrap& copy): ClapTrap(copy.name) // Est ce vraiment comme ca qu'on fait ???
{
	this->name = copy.name;
	this->hitPoints = copy.hitPoints;
	this->energyPoints = copy.energyPoints;
	this->attackDamage = copy.attackDamage;
	std::cout << "A clone of " << copy.name << " has been crafted. Hello twin " << name << std::endl;
}

ScavTrap::~ScavTrap() {std::cout << "ScavTrap " << name << " has been destroyed\n";}

// METHODS //

void	ScavTrap::attack(const std::string& target)
{
	if (!alive_and_awake())
		return ;
	energyPoints--;
	std::cout << "ScavTrap " << name << " has inflicted " << attackDamage << " damages, crushing " << target << std::endl;
}

void	ScavTrap::guardGate() {std::cout << "Scavtrap " << name << " is now in gate keeper mode\n";}
