/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:08:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/31 23:55:35 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Static initialization ///////////////////////////////////////////////////////
const int Fixed::n_fract_bit = 8;

// Constructors and destructors ////////////////////////////////////////////////
Fixed::Fixed(): value(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const int value) // Overflow management ?? + gestion negatifs ?
{
    this->value = value << n_fract_bit;
    std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float value)
{
    std::cout << "float constructor called:\n";
    this->value = (int)roundf((value * pow(2,Fixed::n_fract_bit)));
    // this->value = (int)roundf(value << Fixed::n_fract_bit);
}
// 1234.56 = 1,2345678e3
// First byte = 0000 0011
// Last 3 bytes = 2345678 en bits
// 1. Recup la partie gauche -->
// 2. Recup la partie droite et pouvoir l'arrondir a 8 chiffres apres la virgule 
// 3. pGauche << 8 puis pGauche^pDroite

Fixed::Fixed(const Fixed& copy)
{
    std::cout << "Copy constructor called\n";
    value = copy.getRawBits();
}

Fixed::~Fixed() { std::cout << "Destructor called\n"; }

// Methods ////////////////////////////////////////////////////////////////////

int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called\n";
    return (value);
}

void    Fixed::setRawBits(const int raw) { value = raw; } 

int     Fixed::toInt( void ) const { return (value >> n_fract_bit); }

float   Fixed::toFloat( void ) const { return (value >> Fixed::n_fract_bit); }

// Overloads //////////////////////////////////////////////////////////////////

Fixed&  Fixed::operator=(const Fixed& copy)
{
    std::cout << "Copy assignment operator called\n";
    if (this != &copy)
        value = copy.getRawBits();
    return (*this);
}

std::ostream&    operator<<(std::ostream& os, const Fixed& fixed)
{
    os << fixed.toFloat();
    return (os);
}