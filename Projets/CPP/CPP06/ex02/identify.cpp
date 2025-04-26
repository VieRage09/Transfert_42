/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:10:12 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/27 00:20:29 by tlebon           ###   ########.fr       */
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

void		identify(Base * p)
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

void		identify(Base & p)
{
	std::cout << "Workiin on it\n";
	// A&	aptr = dynamic_cast <A&> (p);
	// B&	bptr = dynamic_cast <B&> (p);
	// C&	cptr = dynamic_cast <C&> (p);

	// if (aptr)
	// 	std::cout << "This object is of type A\n";
	// if (bptr)
	// 	std::cout << "This object is of type B\n";
	// if (cptr)
	// 	std::cout << "This object is of type C\n";
}
