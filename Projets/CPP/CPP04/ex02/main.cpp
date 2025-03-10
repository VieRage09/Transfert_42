/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:15:29 by tlebon            #+#    #+#             */
/*   Updated: 2025/03/10 18:50:52 by tlebon           ###   ########.fr       */
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
