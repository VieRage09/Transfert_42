/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:44:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 21:22:16 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main ( void )
{
	Harl	harald;
	
	harald.complain("DEBUG");
	harald.complain("INFO");
	harald.complain("WARNING");
	harald.complain("ERROR");
	harald.complain("real ERROR");
	return (0);
}