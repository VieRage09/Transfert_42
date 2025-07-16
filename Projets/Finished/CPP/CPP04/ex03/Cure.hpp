/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:39:55 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/07 16:39:56 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CURE_HPP
#define	CURE_HPP

// includes //
#include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		// Default constructor
		Cure();
		// Copy constructor
		Cure(const Cure& copy);
		// Destructor
		~Cure();

		// Methods //
		AMateria* clone() const;
		void use(ICharacter& target);

		// Operators //
		Cure&			operator = (const Cure& copy);

};

#endif // CURE_HPP
