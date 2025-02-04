/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:25:07 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/28 22:11:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name): name(name), weapon(NULL) {}

HumanB::~HumanB() {}

std::string HumanB::getName() const { return (name); }
Weapon      HumanB::getWeapon() const { return (*weapon); }
void        HumanB::setName(std::string& value) { name = value; }
void        HumanB::setWeapon(Weapon& value) { weapon = &value; }

void		HumanB::attack( void ) const
{
	std::cout	<< name << " attacks with their " << getWeapon().getType() << std::endl;
}