/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/15 17:04:03by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BITCOINEXCHANGE_HPP
#define	BITCOINEXCHANGE_HPP

// includes //
#include <iostream>
#include <fstream>
#include <map>
#include <ctime>

class BitcoinExchange
{
	private:

		// attributes //
		std::map<time_t, float>	_db_map;
		
		// private methods //
		std::pair<time_t, float>	create_pair(std::string line, char delim);
		void	display_closest_value(std::pair<time_t, float> pair);


	public:
		// Default constructor
		BitcoinExchange( void );
		// Personnalized constructor
		BitcoinExchange(std::string database);
		// Copy constructor
		BitcoinExchange(const BitcoinExchange& copy);
		// Destructor
		~BitcoinExchange();

		// Methods //
		void	cmpdisplay_file_values(std::string);
		
		// Operators //
		BitcoinExchange&	operator = (const BitcoinExchange& copy);
};

#endif // BITCOINEXCHANGE_HPP
