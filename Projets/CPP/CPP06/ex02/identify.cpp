/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:10:12 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/23 04:42:48 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "identify.hpp"

Base	*	generate( void )
{
	srand(time(NULL));
	int	random = rand() % 3;
	
	if (random == 0)
	{
		std::cout << "New A object\n";
		return (new A());
	}
	else if (random == 1)
	{
		std::cout << "New B object\n";
		return (new B());
	}
	else
	{
		std::cout << "New C object\n";
		return (new C());
	}
}

void		identify(Base * p) // Principle: dynamic cast returns NULL when used to convert to pointer
{
	A*	aptr = dynamic_cast <A*> (p);
	B*	bptr = dynamic_cast <B*> (p);
	C*	cptr = dynamic_cast <C*> (p);

	if (aptr)
		std::cout << "This object is of type A\n";
	if (bptr)
		std::cout << "This object is of type B\n";
	if (cptr)
		std::cout << "This object is of type C\n";
}

void		identify(Base & p) // Principle: dynamic cast throws a bad_cast exception when used to convert to reference
{
	try
	{
		A&	aptr = dynamic_cast <A&> (p);
		std::cout << "This object is of type A\n";
	}
	catch(const std::exception& e) {}
	try
	{
		B&	bptr = dynamic_cast <B&> (p);
		std::cout << "This object is of type B\n";
	}
	catch(const std::exception& e) {}
	try
	{
		C&	cptr = dynamic_cast <C&> (p);
		std::cout << "This object is of type C\n";
	}
	catch(const std::exception& e) {}
}
