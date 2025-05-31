/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:58 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/31 20:28:01 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	check_input(int ac, char **av)
{
	std::string str;

	if (ac < 2)
		throw std::runtime_error("No argument");
	if (ac == 2)
	{
		str = av[1];
		if (str.find_first_not_of("0123456789+ \t") != std::string::npos)
			throw std::runtime_error("No digits arguments");
		return ;
	}
	int	i = 1;
	while (av[i])
	{
		str = av[i];
		if (str.find_first_not_of("0123456789+") != std::string::npos)
			throw std::runtime_error("No digits arguments");
		i++;
	}
}

int	main(int ac, char **av)
{
	try
	{
		check_input(ac, av);
	}
	catch(const std::exception& e)
	{
		return (std::cerr << "[ERROR]: Wrong argument: " << e.what() << std::endl, 1);
	}

	PmergeMe	obj(ac == 2, av);
	obj.display_vec();
	obj.display_deq();
	obj.sort_vector();
	
	// Check input: positive integers only
	// Store input in 2 containers: ?? & ?? ==> Idealement 2 containers avec les meme operations pour pouvoir template --> vector et deque
	// Launch algo on both
	return (0);
}