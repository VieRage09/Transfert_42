/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:21:09 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 17:39:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

// includes //
#include <iostream>

template <typename T>
class Array
{
private:
	// attributes //
	T *_parray;
	unsigned int _length;

public:
	// Default constructor
	Array() : _length(0)
	{
		_parray = new T[0];
		std::cout << "Empty array constructed\n";
	}

	// Personnalized constructor
	Array(unsigned int n) : _length(n)
	{
		_parray = new T[n];
		std::cout << "Array of size " << _length << " constructed\n";
	}

	// Copy constructor
	Array(const Array &copy) : Array(copy._length)
	{
		for (int i = 0; i < copy._length; i++)
			_parray[i] = copy[i];
		std::cout << "Array of length " << copy._length << " copied\n";
	}

	// Destructor
	~Array()
	{
		delete[] _parray;
		std::cout << "Array of length " << _length << " destroyed\n";
	}

	// Methods //
	unsigned int size(void) const
	{
		int size = 0;
		for (int i = 0; i < _length; i++)
			if (_parray[i])
				size++;
		return (size);
	}

	void display_array(void) const
	{
		std::cout << "Displaying array's values: \n";
		for (int i = 0; i < _length; i++)
			std::cout << i << "; " << _parray[i] << std::endl;
	}

	// Getters //
	const unsigned int get_length(void) const { return (_length); }

	// Operators //
	Array &operator=(const Array<T> &copy)
	{
		if (this != &copy)
		{
			delete[] _parray;
			_parray = new T[copy._length];
			_length = copy._length;
			for (int i = 0; i < copy._length; i++)
				_parray[i] = copy[i];
		}
		return (*this);
	}

	T &operator[](unsigned int index) const
	{
		if (index >= _length && _length > 0)
			throw std::out_of_range("[ERROR]: Index is out of range");
		return (_parray[index]);
	}
};

#endif // ARRAY_HPP
