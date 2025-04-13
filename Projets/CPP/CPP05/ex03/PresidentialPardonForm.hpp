/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:39:10 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 22:49:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PRESIDENTIALPARDONFORM_HPP
#define	PRESIDENTIALPARDONFORM_HPP

// includes //
#include "AForm.hpp"


class PresidentialPardonForm : public AForm
{
	private:

		// attributes //
		const std::string			_target;

	public:
		// Default constructor
		PresidentialPardonForm();
		// Personnalized constructor
		PresidentialPardonForm(const std::string & target );
		// Copy constructor
		PresidentialPardonForm(const PresidentialPardonForm& copy);
		// Destructor
		~PresidentialPardonForm();

		// Methods //
		void	execute(Bureaucrat const & executor) const;


		// // Operators //
		// PresidentialPardonForm&	operator = (const PresidentialPardonForm& copy);

		// Getters //
		const std::string&		get_target() const;

};

#endif // PRESIDENTIALPARDONFORM_HPP
