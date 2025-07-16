/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:26:25 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:28:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

// CONSTRUCTORS & DESTRUCTORS //

WrongCat::WrongCat(): WrongAnimal("Cat") {std::cout << "A basic WrongCat is born\n";}

WrongCat::WrongCat(const WrongCat& copy): WrongAnimal(copy.type) {std::cout << "One more lookalike wrong cat in this world\n";}

WrongCat::~WrongCat() {std::cout << "A cat wrong died fighting his own kind (probably)\n";}

// METHODS //

void	WrongCat::makeSound() const {std::cout << "Miaaaaaouaf\n";}

// OPERATORS //

WrongCat& WrongCat::operator = (const WrongCat& copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}
