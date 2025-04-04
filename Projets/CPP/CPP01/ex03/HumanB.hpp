/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:17:19 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 12:04:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB
{
    private:
        std::string name;
        Weapon      *weapon;
    public:
        HumanB(std::string name);
        ~HumanB();
        
        const std::string getName() const;
        const Weapon      getWeapon() const;
        void        setName(std::string& value);
        void        setWeapon(Weapon& value);

        void        attack( void ) const;
};


#endif // HUMANB_H
