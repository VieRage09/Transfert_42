/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:49 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/29 13:20:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <deque>

int	main ( void )
{
	MutantStack<int> ms;
	
	ms.push(4);
	ms.push(2);
	ms.push(1);
	auto it = ms.begin();
	std::cout << *it++ << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *it << std::endl;
	ms.pop();
	it = ms.end();
	it--;
	std::cout << *it << std::endl;
	
	return (0);
}
