/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:34 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/14 18:40:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BITCOINEXCHANGE_HPP
#define	BITCOINEXCHANGE_HPP

// includes //
#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
	private:

		// attributes //
		std::ifstream		_input;
		std::ifstream		_database;
		// Copy constructor
		BitcoinExchange(const BitcoinExchange& copy);

	public:
		// Default constructor
		BitcoinExchange( void );
		// Personnalized constructor
		BitcoinExchange(std::string input, std::string database);
		// Destructor
		~BitcoinExchange();

		// Methods //


		// Operators //
		BitcoinExchange&	operator = (const BitcoinExchange& copy);

		// Getters //
		const std::ifstream&		get_input() const;
		const std::ifstream&		get_database() const;

};

#endif // BITCOINEXCHANGE_HPP
