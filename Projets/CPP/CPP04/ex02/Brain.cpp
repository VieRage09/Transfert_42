/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:42:58 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 12:15:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Brain::Brain()
{
	for(int i = 0; i < 100; i++)
		ideas[i] = "";
	std::cout << "A new Brain has been created\n";
}

Brain::Brain(std::string arr[100])
{
	for (int i = 0; i < 100; i++)
		ideas[i] = arr[i];
	std::cout << "A new Brain has been encoded\n";
}

Brain::Brain(const Brain& copy) // Check for DDDEEEEEEP copy or shallow ???
{
	for (int i = 0; i < 100; i++)
		(this->ideas)[i] = copy.ideas[i];
	std::cout << "A Brain has been copied\n";
}

Brain::~Brain() {std::cout << "A Brain has been destroyed\n";}

// METHODS //


// OPERATORS //

Brain& Brain::operator = (const Brain& copy)
{
	if (this != &copy)
	{
		for (int i = 0; i < 100; i++)
			(this->ideas)[i] = copy.ideas[i];
	}
	return (*this);
}

// GETTERS //

const std::string&	Brain::get_idea(int index) const
{
	if (index > 99)
	{
		std::cerr << "Invalid index\n";
		return (ideas[index % 100]);
	}
	return (ideas[index]);
}

// SETTERS //

void	Brain::set_idea(const std::string& str, int index)
{
	if (index > 99)
	{
		std::cerr << "set_idea: Invalid index\n";
		return ;
	}
	ideas[index] = str;
}