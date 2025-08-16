/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:03:45 by tlebon            #+#    #+#             */
/*   Updated: 2025/08/16 21:18:32 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <sys/socket.h>

bool	check_launch_input(int ac, char **av)
{
	if (ac != 3 || !av[1] || !av[2])
	{
		std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return false;
	}

	std::stringstream	ss;
	std::string	s_port;
	int			port;

	ss << av[1]; 
	ss >> s_port;
	if (s_port.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cerr << "[ERROR] Port number must be digits only\n";
		return (false);
	}
	std::stringstream(s_port) >> port;
	// Modifier pour eviter les ports specifiques a ssh par ex
	if (ss.fail() || port <= 0 || port > 65535)
	{
		std::cerr << "[ERROR] Invalid port number: " << av[1] << std::endl;
		return 1;
	}
	return (true);
}

int	main(int ac, char **av, char **env)
{
	if (!check_launch_input(ac, av))
		return (1);

	int					port = std::stoi(av[1]);
	std::string			passwd = av[2];

	std::cout << "port = " << port << std::endl
			  << "password = " << passwd << std::endl;
	
			  
	// Create a socket

	sockaddr	s_sock_addr;

	s_sock_addr.sa_family = AF_INET;
	s_sock_addr.sa_data = 

	int	sock_fd = socket(AF_INET, SOCK_STREAM || SOCK_NONBLOCK, 0);
	if (sock_fd < 0)
	{
		std::cerr << "[ERROR] socket call failed";
		return (2);
	}
	std::cout << "Sock_fd = " << sock_fd << std::endl;
			  
	return 0;
}