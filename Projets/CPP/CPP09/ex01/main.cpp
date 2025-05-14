/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:01 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/14 17:14:39 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
// Container used: stack

int	main(int ac, char **av)
{
	RPN	rpn_stack;

	if (!rpn_stack.load_stack(av[1]))
		return (1);
	try
	{
		std::cout << rpn_stack.calculate_rpn() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}