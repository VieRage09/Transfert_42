/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:43:08 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 12:30:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	DOG_HPP
#define	DOG_HPP

// includes //
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain	*brain;
	
	public:
		// Default constructor
		Dog();
		// Parametrical constructor
		Dog(Brain *ptr);
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
