/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:31:18 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/23 04:33:42 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERIALIZER_HPP
#define	SERIALIZER_HPP

// includes //
#include <cstdint>
#include "Data.hpp"

// utintptr_t est un int capable de recevoir une valeur convertie d'une void * et la restituer sans changement
class Serializer
{
	private:

		// Default constructor
		Serializer();

	public:
		// Destructor
		~Serializer();

		// Methods //
		static uintptr_t	serialize(Data* ptr);
		static Data*		deserialize(uintptr_t raw);
};

#endif // SERIALIZER_HPP
