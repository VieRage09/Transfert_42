/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:43:46 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:43:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Dog::Dog(): Animal("Dog") {std::cout << "A good dog joined the party\n";}

Dog::Dog(const Dog& copy): Animal(copy.type) {std::cout << "A good dog has been copied (More dog, more joy)\n";}

Dog::~Dog() {std::cout << "A good dog tragically died\n";}

// METHODS //

void	Dog::makeSound() const {std::cout << "OuaaaaaF Ouuuuuuuuaf\n";}

// OPERATORS //

Dog& Dog::operator = (const Dog& copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}
