/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:08:42 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/31 23:45:44 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

// This class represent a fixed number equivalent to fixed<32,8>
// a.k.a a range of 32 bits with the 8 last bit as fractionnal bit
// The binary point "." is therefore inbetween the 3rd and 4th byte 
class Fixed {
    private:
        int                 value;
        static const int    n_fract_bit;

    public:
        Fixed();
        Fixed(const int value);
        Fixed(const float value);
        Fixed(const Fixed& copy);
        ~Fixed();

        int     getRawBits( void ) const;
        void    setRawBits(const int raw);
        
        int     toInt( void ) const;
        float   toFloat( void ) const;

        Fixed&  operator=(const Fixed& copy);
};

std::ostream&    operator<<(std::ostream& os, const Fixed& fixed);

#endif // FIXED_HPP
