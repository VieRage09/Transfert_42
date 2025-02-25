/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:20:56 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:25:56 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

// CONSTRUCTORS & DESTRUCTORS //

WrongAnimal::WrongAnimal() {std::cout << "An unknowned wrong animal just spawned\n";}

WrongAnimal::WrongAnimal(const std::string& str): type(str) {std::cout << "A wrong" << type << " just spawned\n";}

WrongAnimal::WrongAnimal(const WrongAnimal& copy): type(copy.type) {std::cout << "A wrong" << type << " got duplicated\n";}

WrongAnimal::~WrongAnimal()
{
	if (!type.empty())
		std::cout << "A wrong" << type << " has been shot by Eddard, it's now dead\n";
	else
		std::cout << "An wrong unknowned animal has been shot by Eddard, it's now dead\n";
}

// METHODS //

void	WrongAnimal::makeSound() const {std::cout << "Unknowned creepy sound and it feels wrong af\n";}

// OPERATORS //

WrongAnimal& WrongAnimal::operator = (const WrongAnimal& copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}

// GETTERS //

const std::string&	WrongAnimal::getType() const {return (type);}
