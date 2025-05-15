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
#include <string>

class BitcoinExchange
{
	private:

		class Date
		{
			private:
				unsigned int	_year;
				unsigned int	_month;
				unsigned int	_day;
			public:
				Date();
				Date(unsigned int year, unsigned int month, unsigned int day);
				Date(Date & copy);
				~Date();
				

		};
		// attributes //
		std::map<Date, float>	_db_map;

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
		
		// Operators //
		BitcoinExchange&	operator = (const BitcoinExchange& copy);
};

#endif // BITCOINEXCHANGE_HPP
