/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/16 23:03:43 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// CONSTRUCTORS & DESTRUCTORS //

BitcoinExchange::BitcoinExchange( void ) : _db_map() {std::cout << "Default BitcoinExchange instanciated\n";}

BitcoinExchange::BitcoinExchange(std::string db_path) : _db_map()
{
	std::string		line;
	std::fstream	db(db_path);

	// ATTENTION AVANT --> Check si le fichier a bien ete ouvert
	while (!db.eof())
	{
		std::getline(db, line);
		if (line.find_first_of("0123456789") == std::string::npos)
		{
			std::cout << "Line skipped\n";
			continue;
		}
		_db_map.insert(create_pair(line, ','));
	}
	std::cout << "BitcoinExchange object instanciated with " << db_path << " as input\nSize = " << _db_map.size() << std::endl;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) : _db_map(copy._db_map) {std::cout << "BitcoinExchange instance copied\n";}

BitcoinExchange::~BitcoinExchange() {std::cout << "BitcoinExchange object destroyed\n";}

// METHODS //

std::pair<time_t, float>	BitcoinExchange::create_pair(std::string line, char delim)
{
	struct tm	date;
	float		value;
	time_t		timestamp;

	// Attention au test de nazis du parsing genre par de date ou par de value / par de delimitateur
	date.tm_year = std::stoi(line.substr(0, line.find_first_of('-'))) - 1900;
	date.tm_mon = std::stoi(line.substr(line.find_first_of('-') + 1, 2)) - 1;
	date.tm_mday = std::stoi(line.substr(line.find_last_of('-') + 1, 2));
	date.tm_hour = 0;
	date.tm_min = 0;
	date.tm_sec = 0;
	date.tm_isdst = -1;
	value = std::stof(line.substr(line.find_first_of(delim) + 1));
	timestamp = timegm(&date);
	if (timestamp < 0)
		throw std::runtime_error("[ERROR] Invalid date");
	return (std::make_pair(timestamp, value));
}

void	BitcoinExchange::display_closest_value(std::pair<time_t, float> pair)
{
	struct tm 	*date;
	char		str[11];
	float		value;

	date = gmtime(&(pair.first));
	if (strftime(str, 11, "%Y-%m-%d", date) == 0)
	{
		throw std::runtime_error("[ERROR] strftime");
		return ;
	}
	std::cout << str << " => " << pair.second << " = ";
	try
	{
		value = _db_map.at(pair.first);
		std::cout << value * pair.second << std::endl;
	}
	catch(const std::exception& e)
	{
		// Comparer pour chopper la date inferieure la plus proche
		
		
		// std::cout << value * _db_map.lower_bound(value)->second << std::endl;
	}
}

void	BitcoinExchange::cmpdisplay_file_values(std::string path)
{
	if (path.empty())
		throw std::runtime_error("[ERROR] Wrong file path\n");
	std::fstream				input(path);
	std::string					line;
	std::pair<time_t, float> 	tmp;

	// Check si le fichier existe et a bien ete ouvert
	while (!input.eof())
	{
		std::getline(input, line);
		if (line.find_first_of("0123456789") == std::string::npos)
		{
			std::cout << "Line skipped\n";
			continue;
		}
		tmp = create_pair(line, '|');
		if (tmp.second < 0)
			throw std::runtime_error("[ERROR] Not a positive number\n");
		if (tmp.second > 1000)
			throw std::runtime_error("[ERROR] Too large number\n");
		display_closest_value(tmp);
	}


}

// OPERATORS //

BitcoinExchange& BitcoinExchange::operator = (const BitcoinExchange& copy)
{
	if (this != &copy)
		_db_map = copy._db_map;
	return (*this);
}
