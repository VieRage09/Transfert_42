/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:30:28 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/02 18:18:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>

int main(void)
{
	std::vector<float> vec = {1, 2.3, 3, 5};
	try
	{
		std::cout << easyfind(vec, 5) << std::endl;
		std::cout << easyfind(vec, 2) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Value not found\n";
	}

	return (0);
}