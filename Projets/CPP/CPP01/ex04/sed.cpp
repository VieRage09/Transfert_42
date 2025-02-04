/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:15:12 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 16:41:05 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sed.hpp"

// void	sedlike(char *infile, char *to_replace, char *replacement)
void	sedlike(std::string file, std::string to_replace, std::string replacement)
{
	std::string		ofile = file + ".replace";
	std::string		s1 = to_replace;
	std::string		s2 = replacement;
	std::string		line;

	std::ifstream	input_stream(file.c_str());
	if (!input_stream.is_open())
	{
		std::cout << "The file " << file << " doesn't exists\n";
		return ;
	}
	std::ofstream	output_stream(ofile.c_str());
	if (!output_stream.is_open())
	{
		std::cout << "Error happened in the creation of the output file\n";
		return ;
	}
	while (getline(input_stream, line))
	{
		size_t	i = line.find(s1);
		while (i != std::string::npos)
		{
			line.erase(i, s1.size());
			line.insert(i, s2);
			i = line.find(s1);
		}
		output_stream << line << std::endl;
	}
	input_stream.close();
	output_stream.close();
}
