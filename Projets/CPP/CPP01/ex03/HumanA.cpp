/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:12:03 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 17:15:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon): name(name), weapon(weapon) {std::cout << "HumanA built\n";}

HumanA::~HumanA() {std::cout << "HumanA killed\n";}

const std::string HumanA::getName() const { return (name); }
const Weapon      HumanA::getWeapon() const { return (weapon); }
void        HumanA::setName(std::string& value) { name = value; }
void        HumanA::setWeapon(Weapon& value) { weapon = value; }

void		HumanA::attack( void ) const
{
	std::cout	<< name << " attacks with their " << getWeapon().getType() << std::endl;
}
