/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:08 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:51:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BUREAUCRAT_HPP
#define	BUREAUCRAT_HPP

// includes //
#include <iostream> 
#include "AForm.hpp"

class AForm;

class Bureaucrat
{
	private:

		// attributes //
		const std::string	_name;
		int					_grade;

	public:
		// Default constructor
		Bureaucrat();
		// Personnalized constructor
		Bureaucrat(std::string name, int grade);
		// Copy constructor
		Bureaucrat(const Bureaucrat& copy);
		// Destructor
		~Bureaucrat();

		// Methods //
		void				incr_grade();
		void				decr_grade();
		void				signForm(AForm& form);

		// Operators //
		Bureaucrat&			operator = (const Bureaucrat& copy);

		// Getters //
		const std::string&	get_name() const;
		const int&			get_grade() const;

		// Exception classes //
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

std::ostream&		operator << (std::ostream& os, const Bureaucrat& bureaucrat);

#endif // BUREAUCRAT_HPP
