/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:47:41 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:12:28 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Form::Form() : _name("form"), _signed(false), _grade_to_sign(150), _grade_to_exec(150) 
{std::cout << "Basic form created\n";}

Form::Form(std::string name, int grade_to_sign, int grade_to_exec) : _name(name), _signed(false),
	_grade_to_sign(grade_to_sign), _grade_to_exec(grade_to_exec)
{
	if (grade_to_sign < 1 || grade_to_exec < 1)
		throw (Form::GradeTooHighException());
	if (grade_to_sign > 150 || grade_to_exec > 150)
		throw (Form::GradeTooLowException());
	std::cout << name << " form created\n";
}

Form::Form(const Form& copy) : Form(copy._name, copy._grade_to_sign, copy._grade_to_exec)
{std::cout << "Copy of " << copy._name << " created\n";}

Form::~Form() {std::cout << _name << " form destroyed\n";}

// METHODS //

void	Form::beSigned(Bureaucrat const & bureaucrat)
{
	if (bureaucrat.get_grade() <= _grade_to_sign)
		_signed = true;
	else
		throw (Form::GradeTooLowException());
}

// OPERATORS //


// ATTENTION FORNE CANONIQUE
//           vvvvv
// Form& Form::operator = (const Form& copy) // Quel utilitee si les 3/4 des attributs sont const ?????
// {
// 	if (this != &copy)
// 	{
		
// 	}
// 	return (*this);
// }

// GETTERS //

const std::string&	Form::get_name() const { return ( _name );}
const bool&			Form::get_signed() const { return ( _signed );}
const int&			Form::get_grade_to_sign() const { return ( _grade_to_sign );}
const int&			Form::get_grade_to_exec() const { return ( _grade_to_exec );}

// EXCEPTION CLASSES // 
const char	*Form::GradeTooHighException::what() const throw() {return ("[ERROR] Grade is too high\n");}
const char	*Form::GradeTooLowException::what() const throw() {return ("[ERROR] Grade is too low\n");}

// OTHER //
std::ostream&	operator << (std::ostream& os, const Form& form)
{
	os << "Form " << form.get_name() << ":\n\t- Status: ";
	if (form.get_signed())
		os << "signed";
	else
		os << "not signed";
	os	<< "\n\t- grade required to sign: " << form.get_grade_to_sign()
		<< "\n\t- Grade required to execute: " << form.get_grade_to_exec() << std::endl;
	return (os);
}
