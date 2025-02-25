/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:20:47 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:07:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ANIMAL_HPP
#define	ANIMAL_HPP

// includes //
#include <iostream>

class Animal
{
	protected:

		// attributes //
		std::string			type;

	public:
		// Default constructor
		Animal();
		// Personnalized constructor
		Animal(const std::string& str);
		// Copy constructor
		Animal(const Animal& copy);
		// Destructor
		~Animal();

		// Methods //

		virtual void	makeSound() const;

		// Operators //
		Animal&			operator = (const Animal& copy);

		// Getters //
		const std::string&		getType() const;

};

#endif // ANIMAL_HPP
