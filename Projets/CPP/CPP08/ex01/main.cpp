/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:22:56 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/02 19:42:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main( void )
{
	Span	sp(5);
	Span	empty(5);

	sp.add_number(-15000);
	sp.add_number(-15);
	sp.add_number(-1);
	sp.add_number(0);
	sp.add_number(15000);

	sp.display_span();

	std::cout << "Test shortest/longest span member functions\n";
	try
	{
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
		// std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Test Adding too much elements\n";
	try
	{
		sp.add_number(15000);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Test shortest/longestspan member functions with no elements\n";
	try
	{
		std::cout << "Shortest and longest span: " << empty.shortestSpan() << " " << empty.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	
	return (0);
}