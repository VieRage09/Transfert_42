#ifndef	CHARACTER_HPP
#define	CHARACTER_HPP

// includes //
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
	public:
		virtual ~ICharacter() {}
		virtual std::string const & getName() const = 0;
		virtual void equip(AMateria* m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};

class Character : public ICharacter
{
	private:

		// attributes //
		std::string			name;
		AMateria *			inventory[4];
		AMateria ** floor;
		int floor_size;
		int floor_count;

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
