/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:08:51 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/31 18:50:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Constructors and destructors ////////////////////////////////////////////////
Fixed::Fixed(): value(0) {std::cout << "Default constructor called\n";}

Fixed::Fixed(const Fixed& copy)
{
    std::cout << "Copy constructor called\n";
    value = copy.getRawBits();
}

Fixed::~Fixed() {std::cout << "Destructor called\n";}

// Methods ////////////////////////////////////////////////////////////////////

int Fixed::getRawBits( void ) const
{
    std::cout << "getRawBits member function called\n";
    return (value);
}

void    Fixed::setRawBits(int const raw) {value = raw;} 

// Overloads //////////////////////////////////////////////////////////////////

Fixed&  Fixed::operator=(const Fixed& copy)
{
    std::cout << "Copy assignment operator called\n";
    if (this != &copy)
        value = copy.getRawBits();
    return (*this);
}
