/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:23:06 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 17:38:07 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int	main( void )
{
	std::cout << "Creation of a empty int array\n";
	Array<int> aint = Array<int>();
	std::cout << "Displaying array[0]: " << aint[0] << std::endl;
	
	unsigned int	size = 5;
	std::cout << "\nCreation of a float array of size " << size << std::endl;
	Array<float> afloat5 = Array<float>(size);
	afloat5.display_array();
	std::cout << "\nModifying values of float array\n";
	afloat5[2] = 4;
	afloat5[3] = 4.14;
	afloat5.display_array();

	std::cout << "\nTesting copy const and assignement operator\n";
	Array<float> cpy = Array<float>(afloat5);
	Array<float> assign = afloat5;
	std::cout << "Copy array:\n";
	cpy.display_array();
	std::cout << "Assign array:\n";
	assign.display_array();
	std::cout << "Changing values\n";
	cpy[0] = 12.1;
	assign[3] = 9.04;
	std::cout << "OG array:\n";
	afloat5.display_array();
	std::cout << "Copy array:\n";
	cpy.display_array();
	std::cout << "Assign array:\n";
	assign.display_array();

	std::cout << "\nTesting exception on operator []\n";
	try
	{
		afloat5[8] = 2;
		std::cout << "Problems\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "\nSize function\n";
	std::cout << "empty int array size: " << aint.size() << std::endl;
	std::cout << "float array size: " << afloat5.size() << std::endl;
	std::cout << "copy array size: " << cpy.size() << std::endl;
	

	return (0);
}