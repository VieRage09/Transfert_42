/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:31:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/12 02:17:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ROBOTOMYREQUESTFORM_HPP
#define	ROBOTOMYREQUESTFORM_HPP

// includes //
#include "AForm.hpp"
#include <cstdlib>

class RobotomyRequestForm : public AForm
{
	private:

		// attributes //
		const std::string		_target;

	public:
		// Default constructor
		RobotomyRequestForm();
		// Personnalized constructor
		RobotomyRequestForm(const std::string & target);
		// Copy constructor
		RobotomyRequestForm(const RobotomyRequestForm& copy);
		// Destructor
		~RobotomyRequestForm();

		// Methods //
		void	execute(Bureaucrat const & executor) const;


		// // Operators //
		// RobotomyRequestForm&	operator = (const RobotomyRequestForm& copy);

		// Getters //
		const std::string&		get_target() const;

};

#endif // ROBOTOMYREQUESTFORM_HPP
