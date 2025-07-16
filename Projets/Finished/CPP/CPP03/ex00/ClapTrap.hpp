/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:08:53 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 20:46:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap
{
	private:
		std::string	name;
		int			hitPoints;
		int			energyPoints;
		int			attackDamage;

		bool	alive_and_awake();

	public:
	    ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap& copy);
 	   ~ClapTrap();

		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		ClapTrap&	operator = (const ClapTrap& copy);
};

#endif // CLAPTRAP_HPP
