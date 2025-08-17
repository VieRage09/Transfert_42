/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cli.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:25:26 by tlebon            #+#    #+#             */
/*   Updated: 2025/08/17 21:00:12 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

int		ret_error(std::string err_msg, int ret)
{
	std::cerr << "[ERROR] " << err_msg << std::endl;
	return (ret);
}

size_t	strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(int ac, char ** av)
{
	
	if (ac != 3 || !av[1])
	{
		std::cerr << "Usage ./prog port \"msg_to_send\"\n";
		return (1);
	}

	in_port_t port = std::stoi(av[1]);

	std::cout << "Cli port = " << port << std::endl;
	
	sockaddr_in	serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	int	cli_side_sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cli_side_sfd < 0)
		return (ret_error("cli socket call failed", 1));
	if (connect(cli_side_sfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		return (ret_error("cli connect failed", 1));
	std::cout << "Connection established\n";

	char	*buffer = av[2];
	size_t	size_sent = send(cli_side_sfd, buffer, strlen(buffer), 0);
	if (size_sent < 0)
		return (ret_error("send failed", 1));
	std::cout << "Size sent = " << size_sent << std::endl;

	if (close(cli_side_sfd) < 0)
		return (ret_error("close failed", 1));
	return 0;
}