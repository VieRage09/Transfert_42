/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/19 17:15:01 by tlebon           ###   ########.fr       */
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

	std::cout << "\nTEST: gatekeeper mode and attack msg\n";
	a.guardGate();
	a.attack("Pat");
	b.attack("Jack");
	cp.attack("Eddie");
	mmm.attack("Jadou");

	return (0);
}