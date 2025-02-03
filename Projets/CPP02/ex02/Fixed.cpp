/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:08:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/03 20:43:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Static initialization ///////////////////////////////////////////////////////
const int Fixed::n_fract_bit = 8;

////////////////////////////////////////////////////////////////////////////////

// Constructors and destructors ////////////////////////////////////////////////
Fixed::Fixed(): value(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const int value) // Overflow management ??
{
    this->value = value * (1 << Fixed::n_fract_bit);
    std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float value)
{
    std::cout << "Float constructor called:\n";
    this->value = (int)roundf(value * (1 << Fixed::n_fract_bit));
}

Fixed::Fixed(const Fixed& copy)
{
    std::cout << "Copy constructor called\n";
    value = copy.value;
}

Fixed::~Fixed() { std::cout << "Destructor called\n"; }

////////////////////////////////////////////////////////////////////////////////

// Methods ////////////////////////////////////////////////////////////////////
int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called\n";
    return (value);
}

void    Fixed::setRawBits(const int raw) { value = raw; } 

int     Fixed::toInt( void ) const { return (value / (1 << Fixed::n_fract_bit)); }

float   Fixed::toFloat( void ) const { return ((float)value / (1 << Fixed::n_fract_bit)); }

////////////////////////////////////////////////////////////////////////////////

// Overloads //////////////////////////////////////////////////////////////////
Fixed&  Fixed::operator=(const Fixed& copy)
{
    std::cout << "Copy assignment operator called\n";
    if (this != &copy)
        value = copy.value;
    return (*this);
}

bool	Fixed::operator<(const Fixed& other) const
{
	if (this->toFloat() < other.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator>(const Fixed& other) const
{
	if (this->toFloat() > other.toFloat())
		return (true);
	return (false);
}

bool	Fixed::operator<=(const Fixed& other) const
{
	if (this->toFloat() < other.toFloat())
		return (true);
	if (value == other.value)
		return (true);
	return (false);
}

bool	Fixed::operator>=(const Fixed& other) const
{
	if (this->toFloat() > other.toFloat())
		return (true);
	if (value == other.value)
		return (true);
	return (false);
}

bool	Fixed::operator==(const Fixed& other) const
{
	if (value == other.value)
		return (true);
	return (false);
}

bool	Fixed::operator!=(const Fixed& other) const
{
	if (value != other.value)
		return (true);
	return (false);
}

const Fixed	Fixed::operator+(const Fixed& other) const
{
	Fixed	res(this->toFloat() + other.toFloat());
	return (res);
}

const Fixed	Fixed::operator-(const Fixed& other) const
{
	Fixed	res(this->toFloat() - other.toFloat());
	return (res);
}

const Fixed	Fixed::operator*(const Fixed& other) const
{
	Fixed	res(this->toFloat() * other.toFloat());
	return (res);
}

const Fixed	Fixed::operator/(const Fixed& other) const // Ajouter un safe pour division par 0
{
	Fixed	res(this->toFloat() / other.toFloat());
	return (res);
}

Fixed&		Fixed::operator ++ ()
{
	value += (1 / 256);
	return (*this);
}

Fixed		Fixed::operator ++ (int postinc)
{
	Fixed	tmp = *this;
	value += (1 / 256);
	postinc++;
	return (tmp);
}

Fixed&		Fixed::operator -- ()
{
	value -= (1 / 1 << Fixed::n_fract_bit);
	return (*this);
}

Fixed		Fixed::operator -- (int postinc)
{
	Fixed	tmp = *this;
	value -= (1 / 1 << Fixed::n_fract_bit);
	postinc++;
	return (tmp);
}

////////////////////////////////////////////////////////////////////////////////

// Static methods /////////////////////////////////////////////////////////////
Fixed&	Fixed::min(Fixed& f1, Fixed& f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

const Fixed&	Fixed::min(const Fixed& f1, const Fixed& f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed&	Fixed::max(Fixed& f1, Fixed& f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}

const Fixed&	Fixed::max(const Fixed& f1, const Fixed& f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}

////////////////////////////////////////////////////////////////////////////////

// Functions //////////////////////////////////////////////////////////////////
std::ostream&    operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return (os);
}

////////////////////////////////////////////////////////////////////////////////