/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:24:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/11 21:40:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	try
	{
		Form	a;
		Form	b("Green card", 5, 4);
		Form	c(a);

		std::cout << a;
		std::cout << b;
		std::cout << c;
		
		Form	d("Passport", 0, 4);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	try	
	{
		Form	a("ID", 6, 152);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	try
	{
		Bureaucrat	souley("Souleyman", 1);
		Form		a("ID", 6, 5);

		std::cout << souley;
		std::cout << a;
		souley.signForm(a);
		std::cout << souley;
		std::cout << a;

		Form		b("Passport", 1, 1);
		souley.decr_grade();
		std::cout << souley;
		std::cout << b;
		souley.signForm(b);
		std::cout << souley;
		std::cout << b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}