/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:10:53 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 17:33:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <math.h>

template <typename T>
T	display(T elem)
{
	std::cout << elem << std::endl;
	return (elem);
}

void	root(float & x) { x = sqrt(x); }

int	main ( void )
{
	int * numbers = new int [10];
	float * euh = new float [5];
	for(int	i = 0; i < 10; i++)
		numbers[i] = i;
	for(int	i = 0; i < 5; i++)
		euh[i] = static_cast <double> (i) + 0.5;
	iter(numbers, static_cast<size_t>(10), display<int>);
	iter(euh, static_cast<size_t> (5), display<float>);
	iter(euh, 5, root); 
	iter(euh, static_cast<size_t> (5), display<float>);
}