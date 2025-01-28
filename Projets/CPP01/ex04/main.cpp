/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:44:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/28 22:20:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<iostream>

int	main (int ac, char **av)
{
	if (ac < 4)
		std::cout	<< "Usage: ./sed <filename> \"s1\" \"s2\"\nThis program creates"
					<< " a new file named <filename>.replace which is <filename> "
					<< "with every occurences of s1 replaced by s2\n";

	std::string	filename = av[1];
	std::string	s1 = av[2];
	std::string	s2 = av[3];

	
	return (0);
}