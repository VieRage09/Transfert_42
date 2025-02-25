/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:15:29 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/25 15:38:55 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "Basic test:\n";
	const Animal *meta = new Animal();
	const Animal *j = new Dog();
	const Animal *i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); // will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << "\nTest with Wrong cat:\n";
	const	WrongAnimal *a = new WrongAnimal();
	const	WrongAnimal *w = new WrongCat();
	std::cout << a->getType() << " " << std::endl;
	std::cout << w->getType() << " " << std::endl;
	a->makeSound();
	w->makeSound();

	std::cout << "\nTest with WrongCats pointers\n";
	const	WrongCat *wc = new WrongCat();
	std::cout << wc->getType() << " " << std::endl;
	wc->makeSound();

	
	return (0);
}

// int	main()
// {
// 	Dog	a;

// 	return (0);
// }