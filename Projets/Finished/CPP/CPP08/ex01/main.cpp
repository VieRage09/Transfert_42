/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:22:56 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 19:22:30 by tlebon           ###   ########.fr       */
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

	std::cout << "\e[0;32m" << "Test shortest/longest span member functions\n" << "\e[0;37m";
	try
	{
		std::cout << "Longest span: " << sp.longestSpan() << std::endl;
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\e[0;32m" << "Test adding too much elements\n" << "\e[0;37m";
	try
	{
		sp.addNumber(15000);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\e[0;32m" << "Test shortest/longestspan member functions with no elements\n" << "\e[0;37m";
	try
	{
		std::cout << "Shortest and longest span: " << empty.shortestSpan() << " " << empty.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\e[0;32m" << "Test copy const and assignation operator\n" << "\e[0;37m";

	std::cout << "copy constructor from sp\n";
	Span cpy(sp);
	cpy.display_span();
	std::cout << "Assignation empty = cpy\n";
	empty = cpy;
	empty.display_span();

	if (ac == 2)
	{
		std::cout << "\e[0;32m" << "Test with 15000 elements\n" << "\e[0;37m";
		Span fifteen(15000);
		fifteen.add_alot_of_numbers(true);
		fifteen.display_span();
		std::cout << "Shortest and longest span = " << fifteen.shortestSpan() << " " << fifteen.longestSpan() << std::endl;
	}

	std::vector<int>	new_vec;
	Span				new_span(5);
	new_span.addNumber(1);
	new_span.addNumber(2);
	new_span.addNumber(3);
	new_span.addNumber(4);
	new_vec.push_back(5);
	new_vec.push_back(6);
	new_vec.push_back(7);
	new_vec.push_back(8);
	std::cout << "\e[0;32m" << "Test for addRange: Adding elements of new_vec\n" << "\e[0;37m";
	std::cout << "sp before addRange:\n";
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