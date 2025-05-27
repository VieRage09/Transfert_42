/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:47:13 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 15:20:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "whatever.hpp"

int main(void)
{
	std::cout << "\e[0;32m" << "Subject tests\n" << "\e[0;37m";
	int a = 2;
	int b = 3;
	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
	std::cout << "\e[0;32m" << "Additionnal tests\n" << "\e[0;37m";
	bool	tr = 1;
	bool	fa = 0;
	::swap(tr, fa);
	std::cout << "tr = " << tr << ", fa = " << fa << std::endl;
	std::cout << "max( tr, fa ) = " << ::max(tr, fa) << std::endl;
	int		f = 4;
	int		g = 4;
	std::cout << "f = " << f << ", g = " << g << std::endl;
	std::cout << "max( f, g ) = " << ::max(f, g) << std::endl;
	return 0;
}