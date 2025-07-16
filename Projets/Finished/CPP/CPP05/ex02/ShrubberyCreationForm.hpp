/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:36:59 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/12 02:04:29 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SHRUBBERYCREATIONFORM_HPP
#define	SHRUBBERYCREATIONFORM_HPP

// includes //

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:

		// attributes //
		const std::string			_target;

	public:
		// Default constructor
		ShrubberyCreationForm();
		// Personnalized constructor
		ShrubberyCreationForm(const std::string & target );
		// Copy constructor
		ShrubberyCreationForm(const ShrubberyCreationForm & copy);
		// Destructor
		~ShrubberyCreationForm();

		// Methods //
		void	execute(Bureaucrat const & executor) const;

		// Operators //
		// ShrubberyCreationForm&	operator = (const ShrubberyCreationForm& copy);

		// Getters //
		const std::string&		get_target() const;

};

#endif // SHRUBBERYCREATIONFORM_HPP
