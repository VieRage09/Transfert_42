/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:03:45 by tlebon            #+#    #+#             */
/*   Updated: 2025/08/17 20:44:01 tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string.h>

int		ret_error(std::string err_msg, int ret)
{
	std::cerr << "[ERROR] " << err_msg << std::endl;
	return (ret);
}

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

	in_port_t port = std::stoi(av[1]);
	std::string			passwd = av[2];

	std::cout << "Serv port = " << port << std::endl;
	
			  
	// Create a socket

	// Create a struct of internet adress to bind to the port
	sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	int	serv_sfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (serv_sfd < 0)
		return (ret_error("socket call failed", 1));
	if (bind(serv_sfd, (sockaddr *)&addr, sizeof(addr)) < 0)
		return (ret_error("bind failed", 1));
	if (listen(serv_sfd, SOMAXCONN) < 0)
		return (ret_error("listen failed", 1));

	sockaddr_in cli_addr;
	int			cli_sfd = 0;
	socklen_t	len = sizeof(cli_addr);

	while ((cli_sfd = accept(serv_sfd, (sockaddr *)&cli_addr, &len)) < 0)
	{
		perror("accept function pending: ");
		std::cout << "cli_sfd = " << cli_sfd << std::endl;
		sleep(3);
	}
	std::cout << "Connection established\n";

	char	buffer[256];
	memset((void *)buffer, 0, sizeof(buffer));
	size_t	size_recv = recv(cli_sfd, buffer, 255, 0);
	if (size_recv < 0)
		return (ret_error("recv failed", 1));
	std::cout << "Size received = " << size_recv << std::endl;
	std::cout << "Message received = " << buffer << std::endl;

	if (close(serv_sfd) < 0 || close(cli_sfd) < 0)
		return (ret_error("close failed", 1));
	return 0;
}