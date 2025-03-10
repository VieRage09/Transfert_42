/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:15:29 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/10 18:49:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "Array test\n";
	int size = 4;
	Animal *animarray[size];

	for (int i = 0; i < size / 2; i++)
		animarray[i] = new Cat();
	for (int i = size / 2; i < size; i++)
		animarray[i] = new Dog();

	for (int i = 0; i < size; i++)
		animarray[i]->makeSound();

	for (int i = 0; i < size; i++)
		delete animarray[i];

	std::cout << "\n\nLeaks test\n\n";
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;//should not create a leak
	delete i;

	std::cout << "\n\nTest Brain copy is deep\n\n";
	std::string thoughts[100] = {"Eat", "Sleep", "Hunt"};
	Brain	*a = new Brain(thoughts);
	std::cout << a->get_idea(0) << std::endl;
	std::cout << a->get_idea(1) << std::endl;
	std::cout << a->get_idea(2) << std::endl;
	Brain	b(*a);
	a->set_idea("Marcher dans les bois", 0);
	std::cout << a->get_idea(0) << std::endl;
	std::cout << b.get_idea(0) << std::endl;
	delete a;
	std::cout << b.get_idea(0) << std::endl;
	std::cout << b.get_idea(1) << std::endl;
	std::cout << b.get_idea(2) << std::endl;

	std::cout << "\n\nTest Cat copy is deep\n\n";
	Cat *	pip = new Cat (&b);
	Cat *	aza = new Cat (*pip);

	std::cout << pip->getBrain()->get_idea(0) << std::endl;	
	std::cout << pip->getBrain()->get_idea(1) << std::endl;	
	std::cout << pip->getBrain()->get_idea(2) << std::endl;	
	std::cout << aza->getBrain()->get_idea(0) << std::endl;	
	std::cout << aza->getBrain()->get_idea(1) << std::endl;	
	std::cout << aza->getBrain()->get_idea(2) << std::endl;	
	pip->getBrain()->set_idea("La nuit je mens", 0);
	std::cout << pip->getBrain()->get_idea(0) << std::endl;	
	std::cout << aza->getBrain()->get_idea(0) << std::endl;	
	delete pip;
	std::cout << aza->getBrain()->get_idea(0) << std::endl;	
	std::cout << aza->getBrain()->get_idea(1) << std::endl;	
	std::cout << aza->getBrain()->get_idea(2) << std::endl;	
	delete aza;
	return (0);
}


// int	main()
// {
// 	Brain a;

// 	a.set_idea("Salut", 0);
// 	a.set_idea("Slt", 1);
// 	a.set_idea("Goodbye", 3);
// 	std::cout << "First 4 ideas of brain a: " << a.get_idea(0) << "," << a.get_idea(1) << "," << a.get_idea(2) << "," << a.get_idea(3) << "\n";
// 	Cat	patoune(&a);

// 	patoune.makeSound();
// 	return (0);
// }