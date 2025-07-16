/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:08:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/03 18:21:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Static initialization ///////////////////////////////////////////////////////
const int Fixed::n_fract_bit = 8;

// Constructors and destructors ////////////////////////////////////////////////
Fixed::Fixed(): value(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const int value) // Overflow management ?? + gestion negatifs ?
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

// Methods ////////////////////////////////////////////////////////////////////

int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called\n";
    return (value);
}

void    Fixed::setRawBits(const int raw) { value = raw; } 

int     Fixed::toInt( void ) const { return (value / (1 << Fixed::n_fract_bit)); }

float   Fixed::toFloat( void ) const { return ((float)value / (1 << Fixed::n_fract_bit)); }

// Overloads //////////////////////////////////////////////////////////////////

Fixed&  Fixed::operator=(const Fixed& copy)
{
    std::cout << "Copy assignment operator called\n";
    if (this != &copy)
        value = copy.value;
    return (*this);
}

std::ostream&    operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return (os);
}