/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:51:30 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/07 18:39:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

// STATIC INIT //

const int	MateriaSource::temp_size = 4;

// CONSTRUCTORS & DESTRUCTORS //

MateriaSource::MateriaSource()
{
	templates = new AMateria[4];
	std::cout << "MateriaSource constructor called\n";
}

MateriaSource::MateriaSource(const MateriaSource& copy) {}

MateriaSource::~MateriaSource() {std::cout << "MateriaSource destructor called\n";}

// METHODS //


// OPERATORS //

MateriaSource& MateriaSource::operator = (const MateriaSource& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}
