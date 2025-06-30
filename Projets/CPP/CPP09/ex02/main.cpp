/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:58 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/30 19:38:06 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

// Checks the input arguments
// Throws an exception if the input is invalid
void	check_input(int ac, char **av)
{
	std::string str;

	if (ac < 2)
		throw std::runtime_error("Not enough arguments");
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

	PmergeMe	obj(av);

	std::cout << "before sorting: ";
	obj.display_vec();

	obj.launch_sorts();

	std::cout << "after sorting: ";
	obj.display_vec();
	std::cout << std::endl;

	// Display the datas
	std::cout	<< "Time for " << obj.get_size() << " elements with std::vec:\t"
				<< obj.get_time_vec() << " ms." << std::endl
				<< "Comparison / Max comparison =\t\t" << obj.get_vec_comps() << "/" << obj.get_max_nb_comps() << std::endl;
	std::cout	<< "Time for " << obj.get_size() << " elements with std::deq:\t"
				<< obj.get_time_deq() << " ms."<< std::endl
				<< "Comparison / Max comparison =\t\t" << obj.get_deq_comps() << "/" << obj.get_max_nb_comps() << std::endl;

	// Check if the containers are sorted
	std::is_sorted(obj.get_vec().begin(), obj.get_vec().end()) ?
		std::cout << "std::vec is sorted." << std::endl :
		std::cout << "std::vec is NOT sorted." << std::endl;	
	std::is_sorted(obj.get_deq().begin(), obj.get_deq().end()) ?
		std::cout << "std::deq is sorted." << std::endl :
		std::cout << "std::deq is NOT sorted." << std::endl;

	return (0);
}
