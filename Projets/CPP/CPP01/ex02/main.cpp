/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:44:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 20:26:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<iostream>

int	main ( void )
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	*stringPTR = &str;
	std::string	&stringREF = str;

	std::cout	<< "Memory adress of str:            " << &str << std::endl
				<< "Memory adress held by stringPTR: " << &stringPTR << std::endl
				<< "Memory adress held by stringREF: " << &stringREF << std::endl
				<< "Value of str:                  " << str << std::endl
				<< "Value pointed to by stringPTR: " << stringPTR << std::endl	// Ambigu: valeur pointee par un pointeur est une adresse saoule pas stp
				<< "Value pointed to by stringREF: " << stringREF << std::endl;
	return (0);
}