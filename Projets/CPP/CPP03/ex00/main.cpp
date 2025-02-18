/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/18 00:59:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main()
{
	ClapTrap	ct1;
	ClapTrap	ct2("Patoche");
	ClapTrap	ct3(ct1);
	ClapTrap	ct4("Eddy");

	ct4 = ct1;

	std::cout << "\nTest 1: ClapTrap can't do anything if it is dead\n";
	ct1.takeDamage(10);
	ct1.attack("Philou");
	ct1.beRepaired(10);

	std::cout << "\nTest 2: ClapTrap can take damages w/o dying and can be repaired\n";
	ct3.takeDamage(5);
	ct3.beRepaired(3);
	ct3.takeDamage(7);
	ct3.beRepaired(1);
	ct3.takeDamage(2);
	ct3.attack("Philou");

	std::cout << "\nTest 3: ClapTrap can't do anything if it has no energy left\n"; 
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.attack("Philou");
	ct2.beRepaired(3);
	ct2.attack("Philou");
	ct2.attack("Philou");

	return (0);
}