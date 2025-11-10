/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:41:21 by tlebon            #+#    #+#             */
/*   Updated: 2025/10/20 19:37:44 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"
#include "utils.hpp"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctime>

//======================================================================== CommandHandler ========//
#pragma region commandHandler

std::vector<std::string> splitTargets(const std::string& str)
{
    std::vector<std::string> targets;
    std::string::size_type start = 0;
    std::string::size_type end = 0;
    
    while ((end = str.find(',', start)) != std::string::npos)
    {
        targets.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    targets.push_back(str.substr(start));
    return targets;
}

std::string toUpperCase(const std::string& str) // converts a string to uppercase, IRC commands are NOT case sensitive
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::vector<std::string> letMeCook(const std::string& input) //parse the input into command and parameters
{
    if (input.empty()) {
        return std::vector<std::string>();
    }
    
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    
    // skip prefix if present (messages from server/other users start with :)
    if (input[0] == ':') {
        iss >> token; // Read and skip prefix
    }
    // parse command and parameters
    while (iss >> token) {
        if (token[0] == ':') 
        {
            std::string remaining;
            std::getline(iss, remaining);
            token += remaining;
            token = token.substr(1);
            tokens.push_back(token);
            break;
        }
        tokens.push_back(token);
    }
    
    return tokens;
}

#pragma endregion commandHandler
//================================================================================================//

//============================================================================== Overall =========//
#pragma region overall

/**
 * @brief Used to print logs of the server
 * @param msg The message of the log
 * @param output cout / cerr
 * @param color The colour of the log
 */
void	serv_log(std::string msg, std::ostream & output, std::string color)
{
	time_t	now = std::time(NULL);
	std::tm	*t = std::localtime(&now);
	output	<< "["
			<< std::setfill('0') << std::setw(2) << t->tm_hour << ":"
			<< std::setfill('0') << std::setw(2) << t->tm_min << ":"
			<< std::setfill('0') << std::setw(2) << t->tm_sec << "] "
			<< color << msg << RESET << std::endl;
}

#pragma endregion overall
//================================================================================================//