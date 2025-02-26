/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:20:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 15:39:07 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CAT_HPP
#define	CAT_HPP

// includes //
#include "A_Animal.hpp"
#include "Brain.hpp"

class Cat : public A_Animal
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

};

#endif // CAT_HPP
