/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:05:17 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/13 21:32:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	INTERN_HPP
#define	INTERN_HPP

// includes //
#include "AForm.hpp"

class Intern
{
	public:
		// Default constructor
		Intern();
		// Copy constructor
		Intern(const Intern& copy);
		// Destructor
		~Intern();

		// Methods //
		AForm	*makeForm(std::string name, std::string target);

		// Operators //
		Intern&			operator = (const Intern& copy);
};

#endif // INTERN_HPP
