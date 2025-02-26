/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:20:50 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 15:41:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A_Animal.hpp"

// CONSTRUCTORS & DESTRUCTORS //

A_Animal::A_Animal() {std::cout << "(Animal basic ctr) An unknowned animal just spawned\n";}

A_Animal::A_Animal(const std::string& str): type(str) {std::cout << "(Animal param ctr) A " << type << " just spawned\n";}

A_Animal::A_Animal(const A_Animal& copy): type(copy.type) {std::cout << "(Animal cpy ctr) A " << type << " got duplicated\n";}

A_Animal::~A_Animal()
{
	if (!type.empty())
		std::cout << "(Animal des) A " << type << " has been shot by Eddard, it's now dead\n";
	else
		std::cout << "(Animal des) An unknowned animal has been shot by Eddard, it's now dead\n";
}

// METHODS //

void	A_Animal::makeSound() const {std::cout << "Unknowned creepy sound\n";}

// OPERATORS //

A_Animal& A_Animal::operator = (const A_Animal& copy)
{
	if (this != &copy)
	{
		this->type = copy.type;
	}
	return (*this);
}

// GETTERS //

const std::string&	A_Animal::getType() const {return (type);}
