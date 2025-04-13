/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:24:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/13 21:34:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int	main()
{
	try
	{
		AForm	*a = NULL;
		Intern	b;

		a = b.makeForm("robotomy ", "bender");
		if (a)
			std::cout << *a;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
		
}