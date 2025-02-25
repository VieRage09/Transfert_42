/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:26:13 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:26:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Cat::Cat(): Animal("Cat") {std::cout << "A basic Cat is born\n";}

Cat::Cat(const Cat& copy): Animal(copy.type) {std::cout << "One more lookalike cat in this world\n";}

Cat::~Cat() {std::cout << "A cat died fighting his own kind (probably)\n";}

// METHODS //

void	Cat::makeSound() const {std::cout << "MiaaaaaOUUUUUUUUUU\n";}

// OPERATORS //

Cat& Cat::operator = (const Cat& copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}
