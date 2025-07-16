/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:01 by tlebon            #+#    #+#             */
/*   Updated: 2025/07/11 15:02:29 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
// Container used: stack

int	main(int ac, char **av)
{
	RPN	rpn_stack;

	if (ac != 2 || !av[1])
	{
		std::cout << "Usage: " << av[0] << " <RPN expression>\n";
		return (1);
	}
	try
	{
		std::cout << rpn_stack.calculate_rpn(av[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}