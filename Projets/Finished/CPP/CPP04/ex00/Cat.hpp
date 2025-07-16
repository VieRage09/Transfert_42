/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:20:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:08:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CAT_HPP
#define	CAT_HPP

// includes //
#include "Animal.hpp"

class Cat : public Animal
{
	public:
		// Default constructor
		Cat();
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
