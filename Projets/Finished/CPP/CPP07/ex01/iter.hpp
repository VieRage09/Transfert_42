/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:11:16 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/29 18:41:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T, typename F>
void	iter(T *array, size_t size, F func)
{
	for(size_t i = 0; i < size; i++)
	{
		func(array[i]);
	}
}