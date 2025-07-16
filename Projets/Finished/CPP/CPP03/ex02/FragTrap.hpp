/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:57:55 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/18 20:01:08 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp" 

class FragTrap: public ClapTrap
{
	public:
	FragTrap();
	FragTrap(const std::string name);
	FragTrap(const FragTrap& copy);
	~FragTrap();

	void	highFivesGuys( void );
};

#endif // FRAGTRAP_HPP
