/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:20:50 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/10 18:23:43 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Animal::Animal(): type("Chimera") {std::cout << "An unknowned animal just spawned\n";}

Animal::Animal(const std::string& str): type(str) {std::cout << "An animal just spawned\n";}

Animal::Animal(const Animal& copy): type(copy.type) {std::cout << "A " << type << " got duplicated\n";}

Animal::~Animal()
{
	if (!type.empty())
		std::cout << "A " << type << " has been shot by Eddard, it's now dead\n";
	else
		std::cout << "An unknowned animal has been shot by Eddard, it's now dead\n";
}

// METHODS //

void	Animal::makeSound() const {std::cout << "Unknowned creepy sound\n";}

// OPERATORS //

Animal& Animal::operator = (const Animal& copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}

// GETTERS //

const std::string&	Animal::getType() const {return (type);}
