/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:15:29 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/26 15:38:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
	int size = 4;
	A_Animal *animarray[size];

	for (int i = 0; i < size / 2; i++)
		animarray[i] = new Cat();
	for (int i = size / 2; i < size; i++)
		animarray[i] = new Dog();

	for (int i = 0; i < size; i++)
		animarray[i]->makeSound();

	for (int i = 0; i < size; i++)
		delete animarray[i];
	return (0);
}

// int main()
// {
// 	A_Animal a;
// 	return 0;
// }

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