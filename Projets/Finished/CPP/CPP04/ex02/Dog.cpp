/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:43:05 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 15:41:43 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Dog::Dog(): A_Animal("Dog")
{
	brain = new Brain();
	std::cout << "(Dog basic ctr) A good dog joined the party\n";
}

Dog::Dog(Brain *ptr): A_Animal("Dog")
{
	brain = new Brain(*ptr);
	std::cout << "(Dog param ctr) A good dog has been encoded\n";
}

Dog::Dog(const Dog& copy): A_Animal(copy.type)
{
	brain = new Brain(*(copy.brain));
	std::cout << "(Dog cpy ctr) A good dog has been copied (More dog, more joy)\n";
}

Dog::~Dog()
{
	delete brain;
	std::cout << "(Dog dest) A good dog tragically died\n";
}

// METHODS //

void	Dog::makeSound() const {std::cout << "OuaaaaaF Ouuuuuuuuaf\n";}

// OPERATORS //

Dog& Dog::operator = (const Dog& copy)
{
	if (this != &copy)
	{
		delete brain;
		brain = new Brain(*(copy.brain));
		this->type = copy.type;
	}
	return (*this);
}
