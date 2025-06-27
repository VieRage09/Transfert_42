/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:43:58 by tlebon            #+#    #+#             */
/*   Updated: 2025/06/27 19:32:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

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

	PmergeMe	obj(av);

	std::cout << "before sorting:" << std::endl;
	obj.display_vec();

	clock_t v_start = clock();
	obj.sort_vector(2);
	clock_t v_end = clock();
	double v_duration = static_cast<double>(v_end - v_start) / CLOCKS_PER_SEC * 1000;
	unsigned int v_comps = obj.get_nb_comps();
	
	obj.reset_nb_comps();

	clock_t d_start = clock();
	obj.sort_deque(2);
	clock_t d_end = clock();
	double d_duration = static_cast<double>(d_end - d_start) / CLOCKS_PER_SEC * 1000;
	unsigned int d_comps = obj.get_nb_comps();

	std::cout << "after sorting:" << std::endl;
	obj.display_vec();
	std::cout << std::endl;

	std::cout	<< "Time for " << obj.get_size() << " elements with std::vec:\t"
				<< v_duration << " ms." << std::endl
				<< "Comparison / Max comparison =\t\t" << v_comps << "/" << obj.get_max_nb_comps() << std::endl;
	std::cout	<< "Time for " << obj.get_size() << " elements with std::deq:\t"
				<< d_duration << " ms."<< std::endl
				<< "Comparison / Max comparison =\t\t" << d_comps << "/" << obj.get_max_nb_comps() << std::endl;
	std::is_sorted(obj.get_vec().begin(), obj.get_vec().end()) ?
		std::cout << "std::vec is sorted." << std::endl :
		std::cout << "std::vec is NOT sorted." << std::endl;	
	std::is_sorted(obj.get_deq().begin(), obj.get_deq().end()) ?
		std::cout << "std::deq is sorted." << std::endl :
		std::cout << "std::deq is NOT sorted." << std::endl;
	return (0);
}
