/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:01 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/13 21:01:43 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
// Container used: stack

int	main(int ac, char **av)
{
	// Read inputs and store them into stack containers
	// Launch algo rpn calculation:
	// 1. Read stack 3 elements at a time(3 3 3 + invalid) and pop them
	//		--> The first 2 elements shall be integers
	//		--> The third elements shall be an operator
	// 2. Perform the operation -> n1 n3 n2 (4 + 2 for ex)
	// 3. Push the result as a new element to the stack
	// 4. if stack size is > 1
	//		--> back to 1.
	//	  else
	//		--> print last element of the stack as the result
	// ERRORS to manage
	if (ac < 2)
		return (std::cerr << "Error: no arguments\n", 1);

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