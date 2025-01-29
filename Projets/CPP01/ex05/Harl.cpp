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

Harl::Harl(){}

Harl::~Harl(){}

void	Harl::debug( void )
{
	std::cout	<< "[ DEBUG ]\n";
	std::cout	<< "I love having extra bacon for my" 
				<< "7XL-double-cheese-triple-pickle-special-ketchup burger." 
				<< "I really do!\n";
}

void	Harl::info( void )
{
	std::cout	<< "[ INFO ]\n";
	std::cout	<< "I cannot believe adding extra bacon costs more money. "
				<< "You didn't put enough bacon in my burger! If you did, "
				<< "I wouldn't be asking for more!\n";
}

void	Harl::warning( void )
{
	std::cout	<< "[ WARNING ]\n";
	std::cout	<< "I think I deserve to have some extra bacon for free. "
				<< "I've been coming for years whereas you started working "
				<< "here since last month.\n";
}

void	Harl::error( void )
{
	std::cout	<< "[ ERROR ]\n";
	std::cout	<< "This is unacceptable! I want to speak to the manager now.\n";
}

static int get_level(std::string str)
{
	std::string	levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	for (int i = 0; i < 4; i++)
	{
		if (str == levels[i])
			return (i);
	}
	return (-1);
}

void	Harl::complain(std::string level)
{
	void	(Harl::*func_ptr[4])( void ) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	int	lvl = get_level(level);
	if (lvl < 0)
	{
		std::cerr << "Level doesn't exists\n";
		return ;
	}
	(this->*func_ptr[lvl])();
}