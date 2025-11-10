#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

// CommandHandler
std::vector<std::string> splitTargets(const std::string& str);
std::string toUpperCase(const std::string& str);
std::vector<std::string> letMeCook(const std::string& input);

//Overall
void	serv_log(std::string msg, std::ostream & output, std::string color);

#endif
