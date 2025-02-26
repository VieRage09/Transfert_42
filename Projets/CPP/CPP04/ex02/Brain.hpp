/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:42:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 11:48:55 by tlebon           ###   ########.fr       */
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
		// Parametric constructor
		Brain(std::string arr[100]);
		// Copy constructor
		Brain(const Brain& copy);
		// Destructor
		~Brain();

		// Methods //


		// Operators //
		Brain&			operator = (const Brain& copy);
		
		// Getters //
		const std::string&	get_idea(int index) const;

		// Setters //
		void	set_idea(const std::string& str, int index);

};

#endif // BRAIN_HPP
