/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:36:54 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:52:02 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

// CONSTRUCTORS & DESTRUCTORS //

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery creation", 145, 137), _target("void") {std::cout << "Basic ShrubberyCreationForm created\n";}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string & target) : AForm("Shrubbery creation", 145, 137), _target(target)
{std::cout << "ShrubberyCreationForm created for " << target << std::endl;}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& copy) : ShrubberyCreationForm(copy._target)
{std::cout << "Copy of " << copy.get_name() << " created\n";}

ShrubberyCreationForm::~ShrubberyCreationForm() {std::cout << get_name() << " form on " << _target << " destroyed\n";}

// METHODS //

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	
}

// OPERATORS //

// ATTENTION FORME CANNONIQUE (Mais useless la donc bon jcp)

// ShrubberyCreationForm& ShrubberyCreationForm::operator = (const ShrubberyCreationForm& copy)
// {
// 	if (this != &copy)
// 	{
// 	}
// 	return (*this);
// }

// GETTERS //

const std::string&	ShrubberyCreationForm::get_target() const { return ( _target );}
