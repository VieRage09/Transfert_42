/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:44:11 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 11:57:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie( void ) {std::cout << "An anonymous zombie just spawned\n";}

Zombie::Zombie(std::string name): name(name) {std::cout << name << " just spawned\n";}

Zombie::~Zombie( void ) {std::cout << name << " has been destroyed\n";}

void	Zombie::announce( void )
{
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}