/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:08:42 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/31 18:45:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
    private:
        int                 value;
        static const int    n_fract_bit = 8;

    public:
        Fixed();
        Fixed(const Fixed& copy);
        ~Fixed();

        int     getRawBits( void ) const;
        void    setRawBits(int const raw);

        Fixed&  operator=(const Fixed& copy);
};

#endif // FIXED_HPP
