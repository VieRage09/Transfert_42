/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:26:13 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 15:41:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Cat::Cat(): A_Animal("Cat")
{
	brain = new Brain();
	std::cout << "(Cat basic ctr) A basic Cat is born\n";
}

Cat::Cat(Brain *ptr): A_Animal("Cat")
{
	brain = new Brain(*ptr);
	std::cout << "(Cat param ctr) A Cat has been encoded\n";
}

Cat::Cat(const Cat& copy): A_Animal(copy.type)
{
	brain = new Brain(*(copy.brain));
	std::cout << "(Cat cpy ctr) One more lookalike cat in this world\n";
}

Cat::~Cat()
{
	delete brain;
	std::cout << "(Cat dest) A cat died fighting his own kind (probably)\n";
}

// METHODS //

void	Cat::makeSound() const {std::cout << "MiaaaaaOUUUUUUUUUU\n";}

// OPERATORS //

Cat& Cat::operator = (const Cat& copy)
{
	if (this != &copy)
	{
		delete brain;
		brain = new Brain(*(copy.brain));
		this->type = copy.type;
	}
	return (*this);
}
