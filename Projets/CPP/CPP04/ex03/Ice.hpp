#ifndef	ICE_HPP
#define	ICE_HPP

// includes //
#include "AMateria.hpp"

class Ice : public AMateria
{
	public:
		// Default constructor
		Ice();
		// Copy constructor
		Ice(const Ice& copy);
		// Destructor
		~Ice();

		// Methods //
		AMateria* clone() const;
		void use(ICharacter& target);

		// Operators //
		Ice&				operator = (const Ice& copy);

};

#endif // ICE_HPP
