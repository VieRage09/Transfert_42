#ifndef	GENCLASS_HPP
#define	GENCLASS_HPP

#include <iostream>
#include <fstream>

typedef	enum	e_options
{
	ASSIGN_ATTRIBUTES,
	ALL,
	NO_OPTION
}t_options;


// UTILS.CPP // 
std::string	capitalize(std::string& str);
std::string	get_attributes(char **tab);
std::string	get_type(std::string& str);
std::string	get_name(std::string& str);

// WRITE_HEADER.CPP //
bool		write_header_file(std::ofstream& file, std::string& name, t_options opt, char **tab);

// WRITE_CPP.CPP //
bool		write_cpp_file(std::ofstream& file, std::string& name, t_options opt, char **tab);

#endif