/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/18 19:54:59 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main()
{
	ScavTrap	a;
	ScavTrap	b("Maurice");
	ScavTrap	cp(a);
	ScavTrap	mmm;

	mmm = b;

	std::cout << "\nTEST 1: gatekeeper mode and attack msg\n";
	a.guardGate();
	a.attack("Pat");
	mmm.attack("Jadou");

	std::cout << "\nTEST 2: gatekeeper mode and attack msg\n";

	return (0);
}