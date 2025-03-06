#ifndef	CHARACTER_HPP
#define	CHARACTER_HPP

// includes //
#include "ICharacter.hpp"

class Character : public ICharacter
{
	private:

		// attributes //
		std::string			name;
		static const int	inventory_size;
		AMateria *			inventory;

	public:
		// Default constructor
		Character();
		// Personnalized constructor
		Character(std::string const & name);
		// Copy constructor
		Character(const Character& copy);
		// Destructor
		~Character();

		// Methods //
		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);

		// Operators //
		Character&		operator = (const Character& copy);

};

#endif // CHARACTER_HPP
