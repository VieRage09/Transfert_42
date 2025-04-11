/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:47:36 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:12:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FORM_HPP
#define	FORM_HPP

// includes //
#include <iostream>
#include <stdbool.h>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:

		// attributes //
		const std::string	_name;
		bool				_signed;
		const int			_grade_to_sign;
		const int			_grade_to_exec;

	public:
		// Default constructor
		Form();
		// Personnalized constructor
		Form(std::string name, int grade_to_sign, int grade_to_exec);
		// Copy constructor
		Form(const Form& copy);
		// Destructor
		~Form();

		// Methods //
		void				beSigned(Bureaucrat const & bureaucrat);

		// Operators //
		// Form&				operator = (const Form& copy);

		// Getters //
		const std::string&	get_name() const;
		const bool&			get_signed() const;
		const int&			get_grade_to_sign() const;
		const int&			get_grade_to_exec() const;

		// Exception classes
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char	*what() const throw ();
		};
		
		class GradeTooLowException : public std::exception
		{
			public: 
				virtual const char	*what() const throw ();
		};
};

std::ostream&	operator << (std::ostream& os, const Form& form);

#endif // FORM_HPP
