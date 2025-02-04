/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:44:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 16:44:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sed.hpp"

int	main ( void )
{
	std::string	existing_file = "test.txt";
	std::string	existing_file2 = "test2.txt";
	std::string	existing_file3 = "test3.txt";
	std::string	non_existing_file = "Hayce_Lemsi_a_perce";

	sedlike(non_existing_file, "asds", "patoche");
	sedlike(existing_file, "ah oui oui oui", "Ah non !");
	sedlike(existing_file2, "Top !", "Bomboclaaaaat !!");
	sedlike(existing_file3, "i", "ay");
	return (0);
}