/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:10:04 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/06 18:52:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	AMATERIA_HPP
#define	AMATERIA_HPP

// includes //
#include <iostream>
#include "ICharacter.hpp"

class ICharacter;

class AMateria
{
	protected:

		// Attributes //
		std::string	type;

	public:
	
		// Constructeurs & Destructeur //
		AMateria();
		AMateria(std::string const & type);
		AMateria(const AMateria & copy);
		~AMateria();

		// Methods //
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);

		// Getters //
		std::string const & getType() const; //Returns the materia type

		// Operators //
		AMateria &	operator = (const AMateria & copy); // A nettre en pure virtual ?

};

#endif // AMATERIA_HPP
