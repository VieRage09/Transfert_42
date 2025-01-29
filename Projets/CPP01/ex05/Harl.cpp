/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:50:59 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 17:02:06by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::debug( void )
{
	std::cout	<< "[ DEBUG ]\n";
	std::cout	<< "I love having extra bacon for my" 
				<< "7XL-double-cheese-triple-pickle-special-ketchup burger." 
				<< "I really do!";
}

void	Harl::info( void )
{
	std::cout	<< "[ INFO ]\n";
	std::cout	<< "I cannot believe adding extra bacon costs more money. "
				<< "You didn't put enough bacon in my burger! If you did, "
				<< "I wouldn't be asking for more!";
}

void	Harl::warning( void )
{
	std::cout	<< "[ WARNING ]\n";
	std::cout	<< "I think I deserve to have some extra bacon for free. "
				<< "I've been coming for years whereas you started working "
				<< "here since last month.";
}

void	Harl::error( void )
{
	std::cout	<< "[ ERROR ]\n";
	std::cout	<< "This is unacceptable! I want to speak to the manager now.";
}

void	Harl::complain(std::string level)
{
	
	switch (level)
	{
		case :

		default:
			break;
	}
}