/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:08 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/10 16:44:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BUREAUCRAT_HPP
#define	BUREAUCRAT_HPP

// includes //
#include <iostream> 

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
		Bureaucrat(std::string &name, int grade);
		// Copy constructor
		Bureaucrat(const Bureaucrat& copy);
		// Destructor
		~Bureaucrat();

		// Methods //
		void				incr_grade();
		void				decr_grade();

		// Operators //
		Bureaucrat&			operator = (const Bureaucrat& copy);

		// Getters //
		const std::string&	get_name() const;
		const int&			get_grade() const;

		// Exception classes //
		class GradeToHighException : public std::exception
		{
			private:
				const std::string		_error_msg;
			public:
				GradeToHighException(std::string msg);
				virtual const std::string&	GradeToHighException::what();
		};
		
		class GradeToLowException : public std::exception
		{
			private:
				const std::string		_error_msg;
			public:
				GradeToLowException(std::string msg);
				virtual const std::string&	GradeToLowException::what();
		};
};

std::ostream&		operator << (std::ostream& os, const Bureaucrat& bureaucrat);

#endif // BUREAUCRAT_HPP
