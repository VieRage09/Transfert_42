/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:25:22 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/27 15:50:46 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T>
void	swap(T& a, T& b)
{
	T tmp;

	tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
T	min(T a, T b)
{
	try
	{
		if (a < b)
			return (a);
		else
			return (b);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

template <typename T>
T	max(T a, T b)
{
	try
	{
		if (a > b)
			return (a);
		else
			return (b);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

#endif
