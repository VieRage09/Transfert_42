/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:11 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/10 16:49:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Bureaucrat::Bureaucrat(): _name("Fredo"), _grade(150) {std::cout << "Fredo instance created\n";}

Bureaucrat::Bureaucrat(std::string &name, int grade): _name(name)
{
	if (grade < 1)
		throw (Bureaucrat::GradeTooHighException);
	else if (grade > 150)
		throw (Bureaucrat::GradeTooLowException);
	_grade = grade;
	std::cout << name << " instance created\n";
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy): _name(copy._name), _grade(copy._grade)
{
	std::cout << "Copy of " << copy.get_name() << " created\n";
}

Bureaucrat::~Bureaucrat() {std::cout << get_name() << " destroyed\n";}

// METHODS //

void	Bureaucrat::incr_grade()
{
	if (_grade < 2)
		throw (Bureaucrat::GradeTooHighException(""));
	_grade--;
}

void	Bureaucrat::decr_grade()
{
	if (_grade > 149)
		throw (Bureaucrat::GradeTooLowException::what());
	_grade++;
}

// OPERATORS //

Bureaucrat& Bureaucrat::operator = (const Bureaucrat& copy)
{
	if (this != &copy)
		_grade = copy._grade;
	return (*this);
}


// GETTERS //

const std::string&	Bureaucrat::get_name() const { return ( _name );}
const int&	Bureaucrat::get_grade() const { return ( _grade );}

// EXCEPTION CLASSES //

Bureaucrat::GradeToHighException::GradeToHighException(std::string msg) : _error_msg(msg) {}
Bureaucrat::GradeToLowException::GradeToLowException(std::string msg) : _error_msg(msg) {}
const std::string&	Bureaucrat::GradeToHighException::what() {return (_error_msg);}
const std::string&	Bureaucrat::GradeToLowException::what() {return (_error_msg);}

// OTHERS //

std::ostream&	operator << (std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.get_name() << ", bureaucrat grade " << bureaucrat.get_grade() << ".\n";
	return (os);
}
