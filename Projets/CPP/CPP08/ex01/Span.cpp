/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:29:54 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/05 19:56:52 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

// CONSTRUCTORS & DESTRUCTORS //

Span::Span(unsigned int N) : _N(N), _vec(std::vector<int>())
{
	std::cout << "Span of max size " << _N << " created\n";
}

Span::Span(const Span &copy) : _N(copy._N), _vec(std::vector<int>(copy._N))
{
	std::copy(copy._vec.cbegin(), copy._vec.cend(), _vec.begin());
	std::cout << "Span of max size " << _N << " copied\n";
}

Span::~Span() { std::cout << "Span of max size " << _N << " destroyed\n"; }

// CUSTOM METHODS //

void Span::display_span(void) const
{
	std::cout << "The Span tab contains maximum " << _N << " values:\n";
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.cend(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void			Span::add_alot_of_numbers(bool random)
{
	for (int n = 0; n < 15000; n++)
	{
		if (random)
			addNumber(std::rand());
		else
			addNumber(n);
	}
}

// METHODS //

void Span::addNumber(int n)
{
	if (_vec.size() >= _N)
		throw std::out_of_range("Max size reached");
	_vec.push_back(n);
}

void	Span::addRange(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last)
{
	unsigned int size = std::distance(first, last);
	if (_vec.size() + size > _N)
	{
		throw std::runtime_error("Max size reached");
		return ;
	}
	_vec.insert(_vec.end(), first, last);
}
unsigned int Span::shortestSpan() const
{
	unsigned int span = __INT_MAX__;
	std::vector<int> cpy (_N);

	if (_vec.size() <= 1)
		throw std::runtime_error("Span contains less than 2 numbers");
	try
	{
		std::copy(_vec.cbegin(), _vec.cend(), cpy.begin());
		if (!std::is_sorted(cpy.cbegin(), cpy.cend()))
			std::sort(cpy.begin(), cpy.end());
		for (std::vector<int>::iterator it = cpy.begin() + 1; it != cpy.cend(); it++)
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
	return (*std::max_element(_vec.cbegin(), _vec.cend()) - *std::min_element(_vec.cbegin(), _vec.cend()));
}

// OPERATORS //

Span &Span::operator=(const Span &copy)
{
	if (this != &copy)
	{
		_N = copy._N;
		_vec.resize(_N);
		std::copy(copy._vec.begin(), copy._vec.end(), _vec.begin());
		std::cout << "Span of max size " << _N << " assigned\n";
	}
	return (*this);
}

// GETTERS //

const unsigned &Span::get_N() const { return (_N); }
