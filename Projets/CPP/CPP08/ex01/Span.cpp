/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:29:54 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/02 19:41:35 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Span::Span(unsigned int N) : _N(N), _vec(std::vector<int>())
{
	std::cout << "Span of max size " << _N << " created\n";
}

Span::Span(const Span &copy) : _N(copy._N), _vec(std::vector<int>())
{
	std::copy(copy._vec.begin(), copy._vec.end(), _vec.begin());
	std::cout << "Span of max size " << _N << " copied\n";
}

Span::~Span() { std::cout << "Span of max size " << _N << " destroyed\n"; }

// METHODS //

void Span::display_span(void) const
{
	std::cout << "The Span tab contains " << _N << " values:\n";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void Span::add_number(int n)
{
	if (_vec.size() >= _N)
		throw std::out_of_range("Max size reached");
	_vec.push_back(n);
}

unsigned int Span::shortestSpan() const
{
	unsigned int span = __INT_MAX__;
	std::vector<int> cpy;

	if (_vec.size() <= 1)
		throw std::runtime_error("Span contains less than 2 numbers");
	try
	{
		std::copy(_vec.begin(), _vec.end(), cpy.begin());
		if (!std::is_sorted(cpy.begin(), cpy.end()))
			std::sort(cpy.begin(), cpy.end());
		for (std::vector<int>::iterator it = cpy.begin() + 1; it != cpy.end(); it++)
		{
			if (std::abs(*it - *(it - 1)) < span)
				span = std::abs(*it - *(it - 1));
		}
		return (span);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return (-1);
	}
}

unsigned int Span::longestSpan() const
{
	if (_vec.size() <= 1)
		throw std::runtime_error("Span contains less than 2 numbers");
	return (*std::max(_vec.begin(), _vec.end()) - *std::min(_vec.begin(), _vec.end()));
}

// OPERATORS //

Span &Span::operator=(const Span &copy)
{
	if (this != &copy)
	{
		_N = copy._N;
		std::copy(copy._vec.begin(), copy._vec.end(), _vec.begin());
		std::cout << "Span of max size " << _N << " assigned\n";
	}
	return (*this);
}

// GETTERS //

const unsigned &Span::get_N() const { return (_N); }
