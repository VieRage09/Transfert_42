/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:12:30 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/16 16:15:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

std::string	capitalize(char *word)
{
	std::string	captlzed = word;

	for(long unsigned int c = 0; c < captlzed.size(); c++)
		captlzed[c] = std::toupper(captlzed[c]);
	return (captlzed);
}

std::string	megaphone(char **args)
{
	std::string	mega = "";
	int			i = 1;

	while(args[i])
	{
		mega += capitalize(args[i]);
		i++;
		if (args[i])
			mega += ' ';
	}
	return (mega);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	else
		std::cout << megaphone(av) << std::endl;
	return (0);
}
