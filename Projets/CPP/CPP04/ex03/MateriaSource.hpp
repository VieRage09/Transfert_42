/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:51:26 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/08 22:21:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MATERIASOURCE_HPP
#define	MATERIASOURCE_HPP

// includes //
#include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual				~IMateriaSource() {}
		virtual void		learnMateria(AMateria*) = 0;
		virtual AMateria*	createMateria(std::string const & type) = 0;
		virtual	void		printBook() = 0;
};

class MateriaSource : public IMateriaSource
{
	private:

		// attributes //
		AMateria *			book[4];

	public:
		// Default constructor
		MateriaSource();
		// Copy constructor
		MateriaSource(const MateriaSource& copy);
		// Destructor
		~MateriaSource();

		// Methods //
		void		printBook();	
		void		learnMateria(AMateria*);
		AMateria *	createMateria(std::string const & type);
		
		// Operators //
		MateriaSource&	operator = (const MateriaSource& copy);

};

#endif // MATERIASOURCE_HPP
