/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:04:40 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/27 14:30:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "identify.hpp"

int	main( void )
{
	Base * testptr = generate();
	Base & testref = *testptr;
	identify(testptr);
	identify(testref);
	return (0);
}