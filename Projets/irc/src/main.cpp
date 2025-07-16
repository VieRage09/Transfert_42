/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:03:45 by tlebon            #+#    #+#             */
/*   Updated: 2025/07/16 16:10:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>

int	main(int ac, char **av, char **env)
{
	if (ac != 3 || !av[1] || !av[2])
	{
		std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return 1;
	}
	std::stringstream	ss;
	std::string			tmp;
	int					port;
	std::string			passwd;

	ss << av[1]; 
	ss >> tmp;
	std::stringstream(tmp) >> port;
	if (ss.fail() || port <= 0 || port > 65535)
	{
		std::cerr << "Invalid port number: " << av[1] << std::endl;
		return 1;
	}
	passwd = av[2];
	std::cout << "port = " << port << std::endl
			  << "password = " << passwd << std::endl;
	return 0;
}