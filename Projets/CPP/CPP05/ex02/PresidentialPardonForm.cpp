/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:40:29 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/12 02:22:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

// CONSTRUCTORS & DESTRUCTORS //
PresidentialPardonForm::PresidentialPardonForm() : AForm("Presidential pardon", 25, 5), _target("") {std::cout << "Basic PresidentialPardonForm created\n";}

PresidentialPardonForm::PresidentialPardonForm(const std::string & target) : AForm("Presidential pardon", 25, 5), _target(target)
{std::cout << "PresidentialPardonForm created for " << target << std::endl;}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& copy) : PresidentialPardonForm(copy._target)
{std::cout << "Copy of " << copy.get_name() << " created\n";}

PresidentialPardonForm::~PresidentialPardonForm() {std::cout << get_name() << " form on " << _target << " destroyed\n";}

// METHODS //
void	PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (!checkRequirements(executor))
		throw (AForm::GradeTooLowException());
	std::cout << _target << " has been pardonned by his highness mister president Zaphod Beeblebrox\n";
}


// ATTENTION CONNONICAL FORM

// // OPERATORS //

// PresidentialPardonForm& PresidentialPardonForm::operator = (const PresidentialPardonForm& copy)
// {
// 	if (this != &copy)
// 	{

// 	}
// 	return (*this);
// }

// GETTERS //

const std::string&	PresidentialPardonForm::get_target() const { return ( _target );}
