/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:47:36 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:50:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FORM_HPP
#define	FORM_HPP

// includes //
#include <iostream>
#include <stdbool.h>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	private:

		// attributes //
		const std::string	_name;
		bool				_signed;
		const int			_grade_to_sign;
		const int			_grade_to_exec;

	public:
		// Default constructor
		AForm();
		// Personnalized constructor
		AForm(std::string name, int grade_to_sign, int grade_to_exec);
		// Copy constructor
		AForm(const AForm& copy);
		// Destructor
		~AForm();

		// Methods //
		void				beSigned(Bureaucrat& bureaucrat);
		virtual void		execute(Bureaucrat const & executor) const = 0;

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

std::ostream&	operator << (std::ostream& os, const AForm& form);

#endif // FORM_HPP
