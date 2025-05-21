/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:18:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/05/21 18:09:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// CONSTRUCTORS & DESTRUCTORS //

BitcoinExchange::BitcoinExchange( void ) : _db_map() {std::cout << "Default BitcoinExchange instanciated\n";}

BitcoinExchange::BitcoinExchange(std::string db_path) : _db_map()
{
	std::string		line;
	std::ifstream	db(db_path);

	if (db.fail())
		throw std::runtime_error("File does not exist");
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
	db.close();
	std::cout << "BitcoinExchange object instanciated with " << db_path << " as input\nSize = " << _db_map.size() << std::endl;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) : _db_map(copy._db_map) {std::cout << "BitcoinExchange instance copied\n";}

BitcoinExchange::~BitcoinExchange() {std::cout << "BitcoinExchange object destroyed\n";}

// METHODS //

bool	BitcoinExchange::isBisextile(int year)
{
    if(year % 4 == 0){ 
        if(year % 100 == 0){
            if(year % 400 == 0){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

bool	BitcoinExchange::isValidDate(struct tm * date)
{
	int	days_nb[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date->tm_mon < 0 || date->tm_mon > 11)
		return (false);
	if (isBisextile(date->tm_year + 1900))
		days_nb[1] = 29;
	else
		days_nb[1] = 28;
	return (date->tm_mday <= days_nb[date->tm_mon] && date->tm_mday > 0);
}

bool	BitcoinExchange::check_format(std::string line, char delim)
{
	if (line.find_first_of(delim) == std::string::npos
		|| line.find_first_of(delim) != line.find_last_of(delim))
		return (false);

	std::string	date = line.substr(0, line.find_first_of(delim));
	while (date.back() == ' ')
		date.pop_back();

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	if (line.substr(line.find_first_of(delim) + 1).empty()
		|| line.substr(line.find_first_of(delim) + 1).find_first_not_of("0123456789. ") != std::string::npos)
		return (false);
	return (true);
}

std::pair<time_t, float>	BitcoinExchange::create_pair(std::string line, char delim)
{
	struct tm	date;
	float		value;
	time_t		timestamp;

	if (!check_format(line, delim))
		throw std::runtime_error("[ERROR] Bad input: " + line);
	try
	{
		date.tm_year = std::stoi(line.substr(0, line.find_first_of('-'))) - 1900;
		date.tm_mon = std::stoi(line.substr(line.find_first_of('-') + 1, 2)) - 1; // Checkk account l3 pour faire en sorte que ca throw qqch
		date.tm_mday = std::stoi(line.substr(line.find_last_of('-') + 1, 2));
		date.tm_hour = 0;
		date.tm_min = 0;
		date.tm_sec = 0;
		date.tm_isdst = -1;
		value = std::stof(line.substr(line.find_first_of(delim) + 1));
	}
	catch(const std::exception& e)
	{
		throw std::runtime_error("[ERROR] Bad input: " + line);
	}
	if (!isValidDate(&date))
		throw std::runtime_error("[ERROR] Invalid date");
	timestamp = timegm(&date);
	return (std::make_pair(timestamp, value));
}

void	BitcoinExchange::display_closest_value(std::pair<time_t, float> pair)
{
	struct tm 	*date;
	char		str[11];
	float		value;
	
	std::map<time_t, float>::iterator up_bound = _db_map.upper_bound(pair.first);
	up_bound--;
	date = gmtime(&(pair.first));
	if (strftime(str, 11, "%Y-%m-%d", date) == 0)
	{
		throw std::runtime_error("[ERROR] strftime");
		return ;
	}
	std::cout	<< str << " => " << pair.second << " = "
				<< up_bound->second * pair.second
				<< std::endl;
}

void	BitcoinExchange::cmpdisplay_file_values(std::string path)
{
	if (path.empty())
		throw std::runtime_error("[ERROR] Wrong file path\n");

	std::ifstream				input(path);
	std::string					line;
	std::pair<time_t, float> 	tmp;

	if (input.fail())
	{
		throw std::runtime_error("[ERROR] File does not exist");
		return ;
	}
	while (!input.eof())
	{
		std::getline(input, line);
		if (line.find_first_of("0123456789") == std::string::npos)
		{
			std::cout << "Line skipped\n";
			continue;
		}
		try
		{
			tmp = create_pair(line, '|');
			if (tmp.second < 0)
				throw std::runtime_error("[ERROR] Not a positive number");
			if (tmp.second > 1000)
				throw std::runtime_error("[ERROR] Too large number");
			display_closest_value(tmp);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	input.close();
}

// OPERATORS //

BitcoinExchange& BitcoinExchange::operator = (const BitcoinExchange& copy)
{
	if (this != &copy)
		_db_map = copy._db_map;
	return (*this);
}
