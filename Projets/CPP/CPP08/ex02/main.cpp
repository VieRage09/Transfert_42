/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:49 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 19:50:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <deque>

int	main ( void )
{
	MutantStack<int> ms;
	
	ms.push(4);
	// ms.pop();
	auto it = ms.begin();
	std::cout << *it << std::endl;
	
	return (0);
}
