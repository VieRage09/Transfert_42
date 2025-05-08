/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:49 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/08 20:28:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int	main ( void )
{
	MutantStack<int> ms;
	
	if (ms.empty())
		std::cout << "MutantStack is empty\nSize = " << ms.size() << std::endl;
	std::cout << "Pushing 1 to ms\n";
	ms.push(1);
	std::cout	<< std::boolalpha << "Empty: " << ms.empty() << std::endl
				<< "Size: " << ms.size() << std::endl
				<< "Top: " << ms.top() << std::endl;
	std::cout << "Calling pop on ms\n";
	ms.pop();
	std::cout	<< std::boolalpha << "Empty: " << ms.empty() << std::endl
				<< "Size: " << ms.size() << std::endl;

	MutantStack<std::string> mss1(3, "Hello there !");
	std::cout	<< std::boolalpha << "Empty: " << mss1.empty() << std::endl
				<< "Size: " << mss1.size() << std::endl
				<< "Top: " << mss1.top() << std::endl;
	std::cout << "Poping 2 elements then emplace General Kenobi\n";
	mss1.pop();
	mss1.pop();
	mss1.emplace("General Kenobi");
	std::cout	<< std::boolalpha << "Empty: " << mss1.empty() << std::endl
				<< "Size: " << mss1.size() << std::endl
				<< "Top: " << mss1.top() << std::endl;
	MutantStack<std::string> mss2(1, "AAAh the negociator");
	std::cout	<< std::boolalpha << "Empty: " << mss2.empty() << std::endl
				<< "Size: " << mss2.size() << std::endl
				<< "Top: " << mss2.top() << std::endl;
	mss2.swap(mss1);
	std::cout 	<< "mss1 infos:\n";
	std::cout	<< std::boolalpha << "Empty: " << mss1.empty() << std::endl
				<< "Size: " << mss1.size() << std::endl
				<< "Top: " << mss1.top() << std::endl;
	std::cout 	<< "mss2 infos:\n";
	std::cout	<< std::boolalpha << "Empty: " << mss2.empty() << std::endl
				<< "Size: " << mss2.size() << std::endl
				<< "Top: " << mss2.top() << std::endl;

	std::cout	<< "\n\nTrying iterators\n";
	for (auto it = mss2.begin(); it != mss2.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout	<< "checking mss1 != mss2: " << (mss1 != mss2) << std::endl;
	std::cout	<< "checking mss1 == mss2: " << (mss1 == mss2) << std::endl;
	std::cout	<< "checking mss1 > mss2: " << (mss1 > mss2) << std::endl;
	std::cout	<< "checking mss1 >= mss2: " << (mss1 >= mss2) << std::endl;
	std::cout	<< "checking mss1 < mss2: " << (mss1 < mss2) << std::endl;
	std::cout	<< "checking mss1 <= mss2: " << (mss1 <= mss2) << std::endl;
	return (0);
}

// Doc: calling top on empty stack is undefined behavior
