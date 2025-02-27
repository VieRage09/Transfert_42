/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 20:44:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"


int	main()
{
	DiamondTrap	a("Tayo Cruz");
	DiamondTrap	b(a);
	DiamondTrap	c;

	a = c;

	std::cout << "\nTEST 1: gatekeeper mode and attack msg\n";
	a.highFivesGuys();
	a.guardGate();
	a.attack("Pat");
	a.whoAmI();
	b.whoAmI();


	return (0);
}