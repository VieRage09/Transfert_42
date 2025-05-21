/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:07:26 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/21 18:12:25 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
int	main (int ac, char **av)
{
	if (ac != 2)
		return (std::cerr << "Usage: ./btc <file>\n", 1);
	try
	{
		BitcoinExchange	btx("data.csv");
		BitcoinExchange copy = btx;
		btx.cmpdisplay_file_values(av[1]);
		copy.cmpdisplay_file_values(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	// Stocker les valeurs de db dans une map/unordered map
	// Lire la date et la valeur depuis l'input file 
	// Recuperer la ligne correspondant a la date la plus proche dans la db (cf sujet pour "la plus proche") via la map
	// Calculer ratio * valeur de bitcoin
	// Output "Date => valeur = resultat"
	return (0);
}