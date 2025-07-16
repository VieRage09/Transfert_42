/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:45:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/26 23:45:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Serializer::Serializer() {}

Serializer::~Serializer() {}

// METHODS //

uintptr_t	Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast <uintptr_t> (ptr));
}

Data*		Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast <Data*> (raw));
}