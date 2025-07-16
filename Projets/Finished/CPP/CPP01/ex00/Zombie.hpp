/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:40:53 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/28 20:06:39 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie
{
	private:
		std::string	name;
	
	public:
		Zombie(std::string name);
		~Zombie( void );
		void	announce( void );
};

void	randomChump(std::string name);
Zombie* newZombie( std::string name );

#endif