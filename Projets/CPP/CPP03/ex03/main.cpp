/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 13:45:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"


int	main()
{
	DiamondTrap	a;

	std::cout << "\nTEST 1: gatekeeper mode and attack msg\n";
	a.highFivesGuys();
	a.guardGate();
	a.attack("Pat");
	a.whoAmI();
	std::string ou = "Tayo Cruz";
	std::cout << "\n";


	return (0);
}