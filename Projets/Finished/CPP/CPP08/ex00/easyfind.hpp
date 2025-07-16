/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:31:07 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/27 18:43:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>

template <typename T>
const auto &	easyfind(const T & tab, int value)
{
	auto iter = std::find(tab.begin(), tab.end(), value);
	if (iter == tab.end())
		throw std::runtime_error("No match found");
	return (*iter);
}