/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:05:35 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 12:03:50 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

// Constructors
Weapon::Weapon(): type("") {}

Weapon::Weapon(std::string type): type(type) {}

// Destructor
Weapon::~Weapon() {}

// Getters / Setters
const std::string Weapon::getType() const { return (type); }
void		Weapon::setType(std::string name) { type = name; }
