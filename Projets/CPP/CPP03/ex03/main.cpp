/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/18 20:09:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int	main()
{
	FragTrap	a;
	FragTrap	mmm("Zach");

	std::cout << "\nTEST 1: gatekeeper mode and attack msg\n";
	a.highFivesGuys();
	a.attack("Pat");
	mmm.attack("Jadou");


	return (0);
}