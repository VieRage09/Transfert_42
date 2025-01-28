/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:51:19 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/28 20:14:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main( void )
{
	Zombie	*newZ = newZombie("Aymeric");
	if (!newZ)
		return (1);
	newZ->announce();
	randomChump("Patoche");
	delete(newZ);
	return (0);
}