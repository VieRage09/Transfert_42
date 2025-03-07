/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:39:48 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/07 16:39:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
