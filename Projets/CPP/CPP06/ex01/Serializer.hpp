/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:31:18 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/26 23:46:12 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERIALIZER_HPP
#define	SERIALIZER_HPP

// includes //
#include "Data.hpp"

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
