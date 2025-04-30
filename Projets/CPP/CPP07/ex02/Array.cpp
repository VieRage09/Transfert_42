/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:12 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/30 20:29:50 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

// CONSTRUCTORS & DESTRUCTORS //

template <typename T>
Array<T>::Array() : _length(0)
{
	_parray = new T [0];
	std::cout << "Empty array constructed\n";
}

template <typename T>
Array<T>::Array(unsigned int n) : _length(n)
{
	_parray = new T [n];
	std::cout << "Array of size " << _length << " constructed\n";
}

template <typename T>
Array<T>::Array(const Array& copy) : Array<T>(copy._length)
{
	for (int i = 0; i < copy.lenght; i++)
		_parray[i] = copy[i];
	std::cout << "Array of length " << copy.length  << " copied\n";
}

template <typename T>
Array<T>::~Array()
{
	delete[] _parray;
	std::cout << "Array of length " << _length << " destroyed\n";
}

// METHODS //

template <typename T>
unsigned int	Array<T>::size( void ) const
{
	int	size = 0;
	for (int i = 0; i < _length; i++)
		if (_parray[i])
			size++;
	return (size);
}


// OPERATORS //

template <typename T>
Array<T>& Array<T>::operator = (const Array& copy)
{
	if (this != &copy)
	{
		delete[] _parray;
		_parray = new T [copy.length];
		_length = copy._length;
		for (int i = 0; i < copy._length; i++)
			_parray[i] = copy[i];
	}
	return (*this);
}

template <typename T>
T&		Array<T>::operator[] (unsigned int index)
{
	if (index >= _length)
		throw std::exception;
	return (_parray[index]);
}