/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:42:58 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:48:10 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Brain::Brain() {std::cout << "A new Brain has been created\n";}

Brain::Brain(const Brain& copy): ideas(copy.ideas) {std::cout << "A Brain has been copied\n";} // Check for DDDEEEEEEP copy or shallow ???

Brain::~Brain() {std::cout << "A Brain has been destroyed\n";}

// METHODS //


// OPERATORS //

Brain& Brain::operator = (const Brain& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}
