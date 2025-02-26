/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:20:47 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 15:37:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ANIMAL_HPP
#define	ANIMAL_HPP

// includes //
#include <iostream>

class A_Animal
{
	protected:

		// attributes //
		std::string			type;

	public:
		// Default constructor
		A_Animal();
		// Personnalized constructor
		A_Animal(const std::string& str);
		// Copy constructor
		A_Animal(const A_Animal& copy);
		// Destructor
		virtual ~A_Animal();

		// Methods //

		virtual void	makeSound() const = 0;

		// Operators //
		A_Animal&			operator = (const A_Animal& copy);

		// Getters //
		const std::string&		getType() const;

};

#endif // ANIMAL_HPP
