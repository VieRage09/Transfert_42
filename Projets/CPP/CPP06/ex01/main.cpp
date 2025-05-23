/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:45:31 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/23 04:36:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int	main( void )
{
	Data	test(56, 1, 1234567890123456, 12.45, 1234567890123456798.6);
	uintptr_t a = Serializer::serialize(&test);
	Data	*b = Serializer::deserialize(a);

	std::cout	<< "Valeurs de test:\n"
				<< test.c << std::endl
				<< test.i << std::endl
				<< test.l << std::endl
				<< test.f << std::endl
				<< test.ld << std::endl;
	std::cout 	<< "Pointeur de base\t\t=\t" << &test << std::endl
				<< "Valeur apres serialize\t\t=\t" << a << std::endl
				<< "Valeur apres deserialize\t=\t" << b << std::endl;
	std::cout	<< "Valeurs de deserialized:\n"
				<< b->c << std::endl
				<< b->i << std::endl
				<< b->l << std::endl
				<< b->f << std::endl
				<< b->ld << std::endl;
	return (0);
}