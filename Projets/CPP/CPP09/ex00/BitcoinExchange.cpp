/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/14 18:43:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// CONSTRUCTORS & DESTRUCTORS //

BitcoinExchange::BitcoinExchange( void ) : _input(), _database() {std::cout << "Default BitcoinExchange instanciated\n";}

BitcoinExchange::BitcoinExchange(std::string input, std::string database) : _input(input), _database(database)
{
	// Check si les files existent 
	std::cout << "BitcoinExchange object instanciated with " << input << " as input\n";
}

BitcoinExchange::~BitcoinExchange() {std::cout << "BitcoinExchange object destroyed\n";}

// METHODS //


// OPERATORS //

BitcoinExchange& BitcoinExchange::operator = (const BitcoinExchange& copy)
{
	if (this != &copy)
	{
		
	}
	return (*this);
}

// GETTERS //

const std::ifstream&	BitcoinExchange::get_input() const { return ( _input );}
const std::ifstream&	BitcoinExchange::get_database() const { return ( _database );}
