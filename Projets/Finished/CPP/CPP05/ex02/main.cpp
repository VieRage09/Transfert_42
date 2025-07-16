/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:24:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/13 20:59:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int	main()
{
	try
	{
		ShrubberyCreationForm	a("House");
		RobotomyRequestForm		b("Your brother");
		PresidentialPardonForm	c("Shaggy");
		Bureaucrat	pres("Mr President", 1);
		Bureaucrat	mayor("Philippe Lebrun", 104);

		std::cout << a << b << c;
		mayor.signForm(a);
		mayor.signForm(b);
		mayor.signForm(c);
		std::cout << a << b << c;
		mayor.executeForm(a);
		mayor.executeForm(b);
		mayor.executeForm(c);
		std::cout << a << b << c;
		pres.signForm(a);
		pres.signForm(b);
		pres.signForm(c);
		std::cout << a << b << c;
		pres.executeForm(a);
		pres.executeForm(c);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		pres.executeForm(b);
		mayor.executeForm(b);
		mayor.executeForm(c);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
		
}