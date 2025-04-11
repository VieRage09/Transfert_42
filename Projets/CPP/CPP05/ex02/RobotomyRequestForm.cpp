/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:31:47 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:40:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

// CONSTRUCTORS & DESTRUCTORS //

RobotomyRequestForm::RobotomyRequestForm() : AForm("Robotomy request", 72, 45), _target("") {std::cout << "Basic RobotomyRequestForm created\n";}

RobotomyRequestForm::RobotomyRequestForm(const std::string & target) : AForm("Robotomy request", 72 , 45), _target(target)
{std::cout << "RobotomyCreationForm created for " << target << std::endl;}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy) : RobotomyRequestForm(copy._target)
{std::cout << "Copy of " << copy.get_name() << " created\n";}

RobotomyRequestForm::~RobotomyRequestForm() {std::cout << get_name() << " form on " << _target << " destroyed\n";}

// METHODS //


// OPERATORS //


// ATTENTION FORME CANNONIQUE

// RobotomyRequestForm& RobotomyRequestForm::operator = (const RobotomyRequestForm& copy)
// {
// 	if (this != &copy)
// 	{

// 	}
// 	return (*this);
// }

// GETTERS //

const std::string&	RobotomyRequestForm::get_target() const { return ( _target );}
