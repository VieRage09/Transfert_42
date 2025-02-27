/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:44:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/27 16:45:10 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sed.hpp"

int	main (int ac, char **av)
{
	if (ac != 4)
	{
		std::cout << "Usage: ./sedlike <file> <to_replace> <replacement>\n";
		return (1);
	}
	sedlike(av[1], av[2], av[3]);
	return (0);
}