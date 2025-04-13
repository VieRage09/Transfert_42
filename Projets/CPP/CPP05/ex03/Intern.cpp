/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:05:20 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/13 21:34:03 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "string.h"

// CONSTRUCTORS & DESTRUCTORS //

Intern::Intern() {}

Intern::Intern(const Intern& copy) {}

Intern::~Intern() {}

// METHODS //
AForm	*Intern::makeForm(std::string name, std::string target)
{
	AForm	*res = NULL;

	if (strcasecmp(name.c_str(), "Shrubbery Creation") == 0)
		res = new ShrubberyCreationForm(target);
	else if (strcasecmp(name.c_str(), "Robotomy Request") == 0)
		res = new RobotomyRequestForm(target);
	else if (strcasecmp(name.c_str(), "Presidential Pardon") == 0)
		res = new PresidentialPardonForm(target);
	else
	{
		std::cerr << "The form named " << name << " doesn't exist\n";
		return (NULL);
	}
	std::cout << "Intern creates " << name << std::endl;
	return (res);
}


// OPERATORS //

Intern& Intern::operator = (const Intern& copy)
{
	if (this != &copy)
	{
		std::cout << "Whatever\n";
	}
	return (*this);
}
