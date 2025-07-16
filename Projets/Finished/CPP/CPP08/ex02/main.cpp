/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:49 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/29 15:36:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <deque>

int	main ( void )
{
	MutantStack<int> ms;
	MutantStack<int> other;
	
	if (ms.empty())
		std::cout << "Mutant Stack is empty\n";
	ms.push(4);
	ms.push(2);
	ms.push(1);
	other.push(10);
	std::cout << "Mutant Stack size = " << ms.size() << std::endl;
	std::cout << "Top element: " << ms.top() << std::endl;
	ms.swap(other);
	std::cout << "After swap top element: " << ms.top() << std::endl;
	ms.swap(other);
	auto it = ms.begin();
	std::cout << "Displaying ms:\n";
	std::cout << *it++ << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *it << std::endl;
	ms.pop();
	std::cout << "Poping ms\n";
	it = ms.end();
	it--;
	std::cout << "last element: " << *it << std::endl;
	ms = other;
	std::cout << "After assignement top element: " << ms.top() << std::endl;

	std::stack<int> s(ms);
	std::cout << "Copy ms into stack top element: " << s.top() << std::endl;
	return (0);
}
