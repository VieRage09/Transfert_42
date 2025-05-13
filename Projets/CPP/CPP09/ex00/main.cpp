/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:07:26 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/13 16:28:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
//Utilisation container: 

int	main (int ac, char **av)
{
	if (!check_infile(ac, av))
		return (1);	// Throw exception inside check_infile ? + Ajout msg d'erreur
	// Open data.csv --> Check csv format


	// Stocker les valeurs de db dans une map/unordered map
	// Lire la date et la valeur depuis l'input file 
	// Recuperer la ligne correspondant a la date la plus proche dans la db (cf sujet pour "la plus proche") via la map
	// Calculer ratio * valeur de bitcoin
	// Output "Date => valeur = resultat"
	return (0);
}