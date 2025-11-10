/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:27:07 by lberne            #+#    #+#             */
/*   Updated: 2025/10/20 19:30:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include "ircserv.hpp"
#include <string>
#include <vector>

class Server;
class Client;


class CommandHandler 
{
	public:
		static void handleCommand(Server *serv, Client *cli, const std::string& input);
		
		static void handleNick(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleUser(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handlePass(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleJoin(Server *serv, Client *cli, const std::vector<std::string>& params, const std::string& nick);
		static void handlePart(Server *serv, Client *cli, const std::vector<std::string>& params, const std::string& nick);
		static void handlePrivmsg(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleTopic(Server* server, Client* client, const std::vector<std::string>& params);
		static void	handleKick(Server *serv, Client *cli, const std::vector<std::string>& params); 
		static void handleInvite(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleMode(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleNames(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleWho(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleWhois(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handlePing(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handlePong(Client *cli, const std::vector<std::string>& params);
		static void handleQuit(Server *serv, Client *cli, const std::vector<std::string>& params);
		static void handleUnknownCommand(Server *serv, Client *cli, const std::string& command);

	private:
		CommandHandler();
};

#endif
