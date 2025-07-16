/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:58:11 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 20:45:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

// CONSTRUCTORS & DESTRUCTORS //
FragTrap::FragTrap(): ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << name << " is in the BUILDIIIIIING\n";
}

FragTrap::FragTrap(const std::string name): ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap " << name << " is in the BUILDIIIIIING\n";
}

FragTrap::FragTrap(const FragTrap& copy): ClapTrap(copy)
{
	this->hitPoints = copy.hitPoints;
	this->energyPoints = copy.energyPoints;
	this->attackDamage = copy.attackDamage;
	std::cout << "FragTrap " << name << " has been duplicated BANG BANG\n";
}

FragTrap::~FragTrap() {std::cout << "FragTrap " << name << " is tragically DEAD impaled\n";}

// METHODS //

void	FragTrap::highFivesGuys( void ) {std::cout << "Come on guys ! Up top !! :D\nAND HAIL YOUR KING " << name << std::endl;}