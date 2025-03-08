/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:51:30 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/08 22:14:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

// CONSTRUCTORS & DESTRUCTORS //

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		book[i] = NULL;
	std::cout << "MateriaSource constructor called\n";
}

MateriaSource::MateriaSource(const MateriaSource& copy) : MateriaSource()
{
	for (int i = 0; i < 4; i++)
		if (copy.book[i])
			book[i] = copy.book[i]->clone();
	std::cout << "MateriaSource copy contructor called\n";
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
		if (book[i])
			delete book[i];
	std::cout << "MateriaSource destructor called\n";
}

// METHODS //

void	MateriaSource::printBook()
{
	for (int i = 0 ; i < 4; i++)
		if (book[i])
			std::cout << i << ": " << book[i]->getType() << std::endl;
}

void	MateriaSource::learnMateria(AMateria * newMateria)
{
	for (int i = 0 ; i < 4; i++)
	{
		if (book[i] == NULL)
		{
			// book[i] = newMateria->clone();
			book[i] = newMateria;
			std::cout << "New Materia learned : " << newMateria->getType() << std::endl;
			return ;
		}
	}
	std::cout << "[ERROR] The book of MateriaSource is full\n";
}	

AMateria *	MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0 ; i < 4; i++)
		if (book[i]->getType() == type)
			return (book[i]->clone());
	std::cout << "[ERROR] MateriaSource doesn't know any Materia of this type\n";
	return (NULL);
}

// OPERATORS //

MateriaSource& MateriaSource::operator = (const MateriaSource& copy)
{
	if (this != &copy)
	{
		for (int i = 0; i < 4; i++)
		{
			if (copy.book[i])
				book[i] = copy.book[i]->clone();
			else
				book[i] = NULL;
		}
	}
	return (*this);
}
