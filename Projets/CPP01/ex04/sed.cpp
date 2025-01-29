/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:15:12 by tlebon            #+#    #+#             */
/*   Updated: 2025/01/29 13:11:16 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sed.hpp"

void	sedlike(char *infile, char *to_replace, char *replacement)
{
	std::string		file = infile;
	std::string		ofile = infile;
	std::string		s1 = to_replace;
	std::string		s2 = replacement;
	std::string		line;

	std::ifstream	input_file(file.c_str());
	ofile += ".replace";
	std::ofstream	output_file(ofile.c_str());
	
	while (getline(input_file, line))
	{
		size_t	i = line.find(s1);
		while (i != std::string::npos)
		{
			line.erase(i, i + s1.size());
			line.insert(i, s2);
			i = line.find(s1);
		}
		output_file << line << std::endl;
	}
	input_file.close();
	output_file.close();
}