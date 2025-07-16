/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:20:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/10 18:45:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CAT_HPP
#define	CAT_HPP

// includes //
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain	*brain;
		
	public:
		// Default constructor
		Cat();
		// Parametrical constructor
		Cat (Brain *ptr);
		// Copy constructor
		Cat(const Cat& copy);
		// Destructor
		~Cat();

		// Methods //
		void	makeSound() const;

		// Operators //
		Cat&				operator = (const Cat& copy);

		// Getters //
		Brain *	getBrain();

};

#endif // CAT_HPP
