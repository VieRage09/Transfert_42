/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:43:57 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:43:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	WRONGCAT_HPP
#define	WRONGCAT_HPP

// includes //
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	private:

		// attributes //

	public:
		// Default constructor
		WrongCat();
		// Copy constructor
		WrongCat(const WrongCat& copy);
		// Destructor
		~WrongCat();

		// Methods //
		void	makeSound() const;

		// Operators //
		WrongCat&		operator = (const WrongCat& copy);

};

#endif // WRONGCAT_HPP
