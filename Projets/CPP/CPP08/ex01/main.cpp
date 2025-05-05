/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:22:56 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/05 19:56:00 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main(int ac, char **av)
{
	Span sp(5);
	Span empty(5);

	sp.addNumber(-15000);
	sp.addNumber(-15);
	sp.addNumber(15);
	sp.addNumber(0);
	sp.addNumber(15000);

	sp.display_span();

	std::cout << "Test shortest/longest span member functions\n";
	try
	{
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Test Adding too much elements\n";
	try
	{
		sp.addNumber(15000);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Test shortest/longestspan member functions with no elements\n";
	try
	{
		std::cout << "Shortest and longest span: " << empty.shortestSpan() << " " << empty.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "Test copy const and assignation operator\n";

	std::cout << "copy constructor from sp\n";
	Span cpy(sp);
	cpy.display_span();
	std::cout << "Assignation empty = cpy\n";
	empty = cpy;
	empty.display_span();

	if (ac == 2)
	{
		std::cout << "Test with 15 000 numbers\n";
		Span fifteen(15000);
		fifteen.add_alot_of_numbers(true);
		fifteen.display_span();
		std::cout << "Shortest and longest span = " << fifteen.shortestSpan() << " " << fifteen.longestSpan() << std::endl;
	}

	std::vector<int>	new_vec;
	Span				new_span(10);
	new_span.addNumber(1);
	new_span.addNumber(2);
	new_span.addNumber(3);
	new_span.addNumber(4);
	new_vec.push_back(1);
	new_vec.push_back(2);
	new_vec.push_back(3);
	new_vec.push_back(4);
	std::cout << "Test for addRange\nAdding elements of new_vec\nsp before addRange:\n";
	new_span.display_span();
	try
	{
		std::cout << "Sp after addRange:\n";
		new_span.addRange(new_vec.cbegin(), new_vec.cend());
		new_span.display_span();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}

// Main Sujet
// int main()
// {
// 	Span sp = Span(5);
// 	sp.addNumber(6);
// 	sp.addNumber(3);
// 	sp.addNumber(17);
// 	sp.addNumber(9);
// 	sp.addNumber(11);
// 	std::cout << sp.shortestSpan() << std::endl;
// 	std::cout << sp.longestSpan() << std::endl;
// 	return 0;
// }