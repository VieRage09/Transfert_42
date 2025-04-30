/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:12 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/30 19:28:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

// CONSTRUCTORS & DESTRUCTORS //

template<typename T>
Array<T>::Array() {}

template<typename T>
Array<T>::Array(unsigned int n) {}

template<typename T>
Array<T>::Array(const Array& copy) {}

template<typename T>
Array<T>::~Array() {}

// METHODS //


// OPERATORS //

template<typename T>
Array& Array::operator = (const Array& copy)
{
	if (this != &copy)
	{

	}
	return (*this);
}

T&		Array::operator [] () const;