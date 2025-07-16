/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:12:07 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 12:02:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie	*horde = new(std::nothrow) Zombie [N];
	if (!horde)
		return (NULL);
	for (int i = 0; i < N; i++)
	{
		new (horde + i) Zombie(name);
		if (!&horde[i])
		{
			delete[] horde;
			return (NULL);
		}
	}
	return (horde);
}
