#include "DiamondTrap.hpp"

// CONSTRUCTORS & DESTRUCTORS //

DiamondTrap::DiamondTrap(): ClapTrap(), ScavTrap(), FragTrap()
{
	this->name = ClapTrap::name;
	ClapTrap::name = name + "_clap_name"; 
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 30;
	std::cout << "A strange entity has appeared. It says its called " << this->name << ".\n";
}

DiamondTrap::DiamondTrap(const std::string& str): ClapTrap(str), ScavTrap(str), FragTrap(str)
{
	this->name = str;
	ClapTrap::name = this->name + "_clap_name"; 
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 30;
	std::cout << "A strange entity has appeared. It says its called " << this->name << ".\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap& copy): ClapTrap(copy.name), ScavTrap(copy.name), FragTrap(copy.name) 
{
	this->name = copy.name;
	this->ClapTrap::name = copy.ClapTrap::name;
	this->hitPoints = copy.hitPoints;
	this->energyPoints = copy.energyPoints;
	this->attackDamage = copy.attackDamage;
	std::cout << "A strange entity said kage bushin no jutsu. Its says its called " << this->name << " DATEBAYO!\n";
}

DiamondTrap::~DiamondTrap() {std::cout << "The universe ended the life of " << this->name << " :(\n";}

// METHODS //

void	DiamondTrap::whoAmI()
{
	std::cout << "Who am I ? I feel like " << this->name << " but the data says " << this->ClapTrap::name << "--'\n";
}

// OPERATORS //

DiamondTrap& DiamondTrap::operator = (const DiamondTrap& copy)
{
	if (this != &copy)
	{
		this->name = copy.name;
		this->ClapTrap::name = copy.ClapTrap::name;
		this->hitPoints = copy.hitPoints;
		this->energyPoints = copy.energyPoints;
		this->attackDamage = copy.attackDamage;
	}
	return (*this);
}

// GETTERS //

const std::string&	DiamondTrap::getname() const { return ( name );}

// GETTERS //

void	DiamondTrap::setname(std::string& value) { this->name = value; }
