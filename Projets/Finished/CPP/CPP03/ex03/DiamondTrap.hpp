#ifndef	DIAMONDTRAP_HPP
#define	DIAMONDTRAP_HPP

// includes //
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap // public ?
{
	private:

		// attributes //
		std::string			name;

	public:
		// Default constructor
		DiamondTrap();
		// Personnalized constructor
		DiamondTrap(const std::string& str);
		// Copy constructor
		DiamondTrap(const DiamondTrap& copy);
		// Destructor
		~DiamondTrap();

		// Methods //
		void	attack (const std::string& target);
		void	whoAmI();

		// Operators //
		DiamondTrap&		operator = (const DiamondTrap& copy);

		// Getters //
		const std::string&		getname() const;

		// Setters //
		void				setname(std::string& value);

};

#endif // DIAMONDTRAP_HPP
