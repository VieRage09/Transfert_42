/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 00:42:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/19 17:17:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int	main()
{
	FragTrap	a;
	FragTrap	b("Zach");
	FragTrap	cp(a);
	FragTrap	d;

	d = b;

	std::cout << "\nTEST: High five and damages\n";
	a.highFivesGuys();
	a.attack("Pat");
	b.attack("John");
	cp.attack("Jacob");
	d.attack("Eriksen");


	return (0);
}