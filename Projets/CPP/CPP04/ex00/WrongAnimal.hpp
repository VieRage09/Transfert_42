/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:04 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:23:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	WRONGANIMAL_HPP
#define	WRONGANIMAL_HPP

// includes //
#include <iostream>

class WrongAnimal
{
	protected:

		// attributes //
		std::string			type;

	public:
		// Default constructor
		WrongAnimal();
		// Personnalized constructor
		WrongAnimal(const std::string& str);
		// Copy constructor
		WrongAnimal(const WrongAnimal& copy);
		// Destructor
		~WrongAnimal();

		// Methods //

		void	makeSound() const;

		// Operators //
		WrongAnimal&			operator = (const WrongAnimal& copy);

		// Getters //
		const std::string&		getType() const;
};

#endif // WRONGANIMAL_HPP
