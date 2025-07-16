/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:51:19 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/06 15:06:44 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main( void )
{
	int	N = 5;
	Zombie	*horde = zombieHorde(N, "Johnny");
	if (!horde)
		return (1);
	for (int i = 0; i < N; i++)
		horde[i].announce();
	delete[](horde);
	return (0);
}