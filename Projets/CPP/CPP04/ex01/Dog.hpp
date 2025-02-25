/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:43:08 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:43:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	DOG_HPP
#define	DOG_HPP

// includes //
#include "Animal.hpp"

class Dog : public Animal
{
	public:
		// Default constructor
		Dog();
		// Copy constructor
		Dog(const Dog& copy);
		// Destructor
		~Dog();

		// Methods //
		void	makeSound() const;

		// Operators //
		Dog&				operator = (const Dog& copy);
};

#endif // DOG_HPP
