#include "Server.hpp"

#include <iostream>
#include <sstream>
#include <signal.h>		// for interuption

static in_port_t	str_to_port(std::string str)
{
	std::istringstream	iss(str);
	long 				port;

	if (!(iss >> port) || !iss.eof() || port < 1024 || port > 65535)
		throw std::runtime_error("Invalid port number");
	return (static_cast<in_port_t>(port));
}

int	main(int ac, char **av)
{
	in_port_t	port;
	std::string	password;

	if (ac != 3)
	{
		std::cerr << "Not enough params : ./ircserv <port> <passw>"<< '\n';
		return (1);
	}
	try
	{
		port = str_to_port(av[1]);
		password = av[2]; // Check mdp policy ???
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}

	Server serv(port, av[2]);

	try
	{
		signal(SIGINT, Server::handle_signal);
		signal(SIGQUIT, Server::handle_signal);
		serv.init_serv();
		serv.loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << "[Exception thown]: "<< e.what() << '\n';
		serv.shutdown();
		// On doit pouvoir tout bien fermer ici
		return (1);
	}
	serv.shutdown();
	std::cout << GREEN << "Server stopped with success" << RESET << std::endl;
	return (0);
}
	