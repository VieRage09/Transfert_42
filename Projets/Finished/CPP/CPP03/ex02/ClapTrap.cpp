/* --- ClapTrap.cpp --- */

/* ------------------------------------------
author: Tlebon
date: 2/18/2025
------------------------------------------ */

#include "ClapTrap.hpp"

// CONSTRUCTORS & DESTRUCTORS //

ClapTrap::ClapTrap(): name("Sebulba"), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "Default constructor called: ClapTrap Sebulba is created\n";
}

ClapTrap::ClapTrap(std::string name): name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "Constructor called: ClapTrap " << name << " is created\n";
}

ClapTrap::ClapTrap(const ClapTrap& copy): name(copy.name), hitPoints(copy.hitPoints), energyPoints(copy.energyPoints), attackDamage(copy.attackDamage)
{	
	std::cout << "Copy constructor called on " << copy.name << std::endl;
}

ClapTrap::~ClapTrap() {std::cout << "Destructor called on " << name << std::endl;}

// METHODS //

bool	ClapTrap::alive_and_awake()
{
	if (hitPoints > 0 && energyPoints > 0)
		return (true);
	std::cout << "ClapTrap " << name << " can't do anything";
	if (hitPoints > 0)
		std::cout << " (has no energy left)\n";
	if (energyPoints > 0)
		std::cout << " (is dead)\n";
	return (false);
}

void	ClapTrap::attack(const std::string& target)
{
	if (!alive_and_awake())
		return ;
	energyPoints--;
	std::cout << "ClapTrap " << name << " has inflicted " << attackDamage << " damages to " << target << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (hitPoints <= 0)
		std::cout << "ClapTrap " << name << "is already dead\n";
	hitPoints -= amount;
	std::cout << "ClapTrap " << name << " has taken " << amount << " damages\n";
	if (hitPoints <= 0)
		std::cout << "ClapTrap " << name << " is dead\n";
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (!alive_and_awake())
		return ;
	energyPoints--;
	hitPoints += amount;
	std::cout << "ClapTrap " << name << " repairs itself and gets " << amount << " hit points back\n";
	// if (hitPoints > 10)
	// 	hitPoints = 10;
}


// OPERATOR //

ClapTrap& ClapTrap::operator = (const ClapTrap& copy)
{
	if (this != &copy)
	{
		this->name = copy.name;
		this->hitPoints = copy.hitPoints;
		this->energyPoints = copy.energyPoints;
		this->attackDamage = copy.attackDamage;
	}
	std::cout << "Assignement operator called\n";
	return (*this);
}