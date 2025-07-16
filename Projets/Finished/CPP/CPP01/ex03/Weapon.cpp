/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:05:35 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 17:17:52 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// Constructors
Weapon::Weapon(): type("") {std::cout << "Unknowned Weapon created\n";}

Weapon::Weapon(std::string type): type(type) {std::cout << "Weapon of type " << type << " created\n";}

// Destructor
Weapon::~Weapon() {std::cout << "Weapon of type " << type << " destroyed\n";}

// Getters / Setters
const std::string Weapon::getType() const { return (type); }
void		Weapon::setType(std::string name) { type = name; }
