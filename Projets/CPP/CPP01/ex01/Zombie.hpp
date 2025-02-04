/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:40:53 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/28 20:34:28 by tlebon           ###   ########.fr       */
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
		Zombie( void );
		Zombie(std::string name);
		~Zombie( void );
		void	announce( void );
};

Zombie* zombieHorde( int N, std::string name );

#endif