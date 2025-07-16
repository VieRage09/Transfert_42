/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:08:03 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/10 19:11:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main()
{
	// Creation + methods sans exceptions
	// Fin par Creation grade too low
	try
	{
		Bureaucrat jo("Joseph", 1);
		Bureaucrat souley("Souleyman", 75);
		Bureaucrat jah("Jah", 150);
		std::cout << jo;
		std::cout << souley;
		std::cout << jah;
		jo.decr_grade();
		jah.incr_grade();
		std::cout << jo;
		std::cout << souley;
		std::cout << jah;
		Bureaucrat bob("Bobby", 151);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	// Creation Grade too high
	try
	{
		Bureaucrat pat("Patrick", 0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	// Grade too high pour incr_grade
	try
	{
		Bureaucrat jo("Joseph", 1);
		jo.incr_grade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	// Grade too low pour decr_grade
	try
	{
		Bureaucrat jah("Jah", 150);
		jah.decr_grade();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
	
	
	
	
	
	return (0);
}