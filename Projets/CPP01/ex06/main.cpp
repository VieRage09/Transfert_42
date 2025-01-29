/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:44:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 21:45:54 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main (int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Which filter you wanna apply to eternal Harl ?\n";
		return (1);
	}
	Harl	harald;
	
	harald.complain(av[1]);
	return (0);
}