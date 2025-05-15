/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/15 17:52:06 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// CONSTRUCTORS & DESTRUCTORS //

// -- Date -- //
BitcoinExchange::Date::Date() : _year(0), _month(0), _day(0) {std::cout << "Default date object instanciated\n";}

BitcoinExchange::Date::Date(unsigned int year, unsigned int month, unsigned int day) // A la place on peut mettre ce constructeur en private et utiliser une fonction static pour instancier la Date
{
	if (year > 2025 || month > 12 || month == 0 || day > 31 || day == 0)
		throw std::runtime_error("Invalid date format");
	if ((month >= 8 && month % 2 == 1 && day > 30) || (month < 8) && month % 2 == 0 && day > 30 || month == 2 && day > 28)
		throw std::runtime_error("Date doesn't exist");
	std::cout << "Default date object instanciated\n";
}

BitcoinExchange::Date::Date(Date & copy) : Date(copy._year, copy._month, copy._day) {std::cout << "Date object copied\n";}

BitcoinExchange::Date::~Date() {std::cout << "Date object destroyed\n";}
// -- Date -- //

// -- BitcoinExchange -- //
BitcoinExchange::BitcoinExchange( void ) : _db_map() {std::cout << "Default BitcoinExchange instanciated\n";}

BitcoinExchange::BitcoinExchange(std::string database) : _db_map()
{
	std::string line;
	std::fstream	db(database);
	unsigned int	year;
	unsigned int	month;
	unsigned int	day;

	// ATTENTION AVANT --> Check si le fichier a bien ete ouvert
	std::getline(db, line);
	while (!db.eof())
	{
		year = std::stoi(line.substr(0, line.find_first_of('-')));
		month = std::stoi(line.substr(line.find_first_of('-'), line.find_last_of('-')));
		day = std::stoi(line.substr(line.find_last_of('-'), line.find_first_of(',')));
		Date	date(year, month, day);
		float	value = std::stof(line.substr(line.find_first_of(',')));
		_db_map.insert(date, value);
		std::getline(db, line);
	}
	std::cout << "BitcoinExchange object instanciated with " << database << " as input\n";
}

BitcoinExchange::~BitcoinExchange() {std::cout << "BitcoinExchange object destroyed\n";}
// -- BitcoinExchange -- //

// METHODS //


// OPERATORS //

BitcoinExchange& BitcoinExchange::operator = (const BitcoinExchange& copy)
{
	if (this != &copy)
	{
		
	}
	return (*this);
}
