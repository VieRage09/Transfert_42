/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:06:44 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/18 19:56:20 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
	public:
		ScavTrap();
		ScavTrap(const std::string name);
		ScavTrap(const ScavTrap& copy);   
		~ScavTrap();

		void	guardGate();
		void	attack(const std::string& target);
};

#endif // SCAVTRAP_HPP
