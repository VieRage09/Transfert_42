/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:42:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:45:08 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BRAIN_HPP
#define	BRAIN_HPP

// includes //
#include <iostream>

class Brain
{
	private:
		// attributes //
		std::string	ideas[100];	
	public:
		// Default constructor
		Brain();
		// Copy constructor
		Brain(const Brain& copy);
		// Destructor
		~Brain();

		// Methods //


		// Operators //
		Brain&			operator = (const Brain& copy);

};

#endif // BRAIN_HPP
