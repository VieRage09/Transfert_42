/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:32:33 by lberne            #+#    #+#             */
/*   Updated: 2025/10/20 20:14:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ircserv.hpp"
#include "CommandHandler.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "NumericReplies.hpp"
#include "Bot.hpp"
#include "utils.hpp"

#include <iostream>
#include <sstream>


void CommandHandler::handleCommand(Server *serv, Client *cli, const std::string& input) 
{
    std::vector<std::string> tokens = letMeCook(input);
    
    if (tokens.empty() || !serv || !cli)
        return;
    
    std::string command = toUpperCase(tokens[0]);
    std::vector<std::string> params(tokens.begin() + 1, tokens.end());
    
	std::cout << WHITE << "Executing: " << input << std::endl;
    switch (cli->getState())
    {
        case WAITING_PASS: {

            if (command == "PASS") 
                handlePass(serv, cli, params);
            else if (command != "CAP")
                serv->append_client_sBuff(cli, NumericReplies::notRegisteredReply());
			if (command == "NICK" || command == "USER")
			{
				std::string errMsg = NumericReplies::needMoreParamsReply("*", "PASS");
   			    std::string kill_msg = ":" + Server::get_server_name() + " KILL " + params[0] + ":Missing password\r\n";
				send(cli->getFd(), errMsg.c_str(), errMsg.size(), MSG_DONTWAIT);
				send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
				cli->setState(KILLED);
			}
            break;
        }

        case WAITING_NICK: {

            if (command == "NICK") 
                handleNick(serv, cli, params);
            else
                serv->append_client_sBuff(cli, NumericReplies::notRegisteredReply());
            break;
        }

        case WAITING_USER: {

            if (command == "USER") 
                handleUser(serv, cli, params);
            else
                serv->append_client_sBuff(cli, NumericReplies::notRegisteredReply());
            break;
        }

        case REGISTERED: {

            if (command == "NICK")
                handleNick(serv, cli, params);

            else if (command == "JOIN")
                handleJoin(serv, cli, params, cli->getNick());

            else if (command == "PART")
                handlePart(serv, cli, params, cli->getNick());

            else if (command == "PRIVMSG")
                handlePrivmsg(serv, cli, params);

            else if (command == "TOPIC")
                handleTopic(serv, cli, params);

            else if (command == "INVITE")
                handleInvite(serv, cli, params);

            else if (command == "KICK")
                handleKick(serv, cli, params);

            else if (command == "MODE")
                handleMode(serv, cli, params);

            else if (command == "NAMES")
                handleNames(serv, cli, params);

            else if (command == "WHO")
                handleWho(serv, cli, params);

            else if (command == "WHOIS")
                handleWhois(serv, cli, params);

            else if (command == "PING")
                handlePing(serv, cli, params);

            else if (command == "PONG")
                handlePong(cli, params);

            else if (command == "QUIT")
                handleQuit(serv, cli, params);

            else
		        handleUnknownCommand(serv, cli, command);
            break;
        }

        default: {
            break;
        }
    }
}

void CommandHandler::handlePass(Server *serv, Client *cli, const std::vector<std::string>& params){
    if (cli->getState() == REGISTERED)
    {
        serv->append_client_sBuff(cli, NumericReplies::alreadyRegisteredReply(cli->getNick()));
        return ;
    }
    if (params.empty())
	{
		std::string errMsg = NumericReplies::needMoreParamsReply(cli->getNick(), "PASS");
        std::string kill_msg = ":" + Server::get_server_name() + " KILL " + ":Not enough parameter for PASS\r\n";
		send(cli->getFd(), errMsg.c_str(), errMsg.size(), MSG_DONTWAIT);
		send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
		cli->setState(KILLED);
        return ;
    }
    if (params.front().compare(serv->get_password()) == 0)
	{
        cli->setPassOk(true);
        cli->setState(WAITING_NICK);
    }
	else
	{
		std::string errMsg = NumericReplies::passwordMismatchReply();
        std::string kill_msg = ":" + Server::get_server_name() + " KILL " + params[0] + ":Wrong password\r\n";
		send(cli->getFd(), errMsg.c_str(), errMsg.size(), MSG_DONTWAIT);
		send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
		cli->setState(KILLED);
	}
}

void CommandHandler::handleNick(Server *serv, Client *cli, const std::vector<std::string>& params){
    if (params.empty()){
		if (cli->getState() != REGISTERED)
		{
			std::string errMsg = NumericReplies::noNicknameGivenReply("*");
  		    std::string kill_msg = ":" + Server::get_server_name() + " KILL " + ":No nickname given\r\n";

			send(cli->getFd(), errMsg.c_str(), errMsg.size(), MSG_DONTWAIT);
			send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
			cli->setState(KILLED);
		}
		else
        	serv->append_client_sBuff(cli, NumericReplies::noNicknameGivenReply(cli->getNick()));
        return ;
    }
    if (!serv->get_reg().isValidNick(params[0])){
		if (cli->getState() != REGISTERED)
		{
			std::string errMsg = NumericReplies::noNicknameGivenReply("*");
  		    std::string kill_msg = ":" + Server::get_server_name() + " KILL " + params[0] + ":Invalid nickname\r\n";

			send(cli->getFd(), errMsg.c_str(), errMsg.size(), MSG_DONTWAIT);
			send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
			cli->setState(KILLED);
		}
		else
     		serv->append_client_sBuff(cli, NumericReplies::erroneousNicknameReply(cli->getNick(), params[0]));
        return ;
    }

    if (cli->getState() == REGISTERED)
    {
        std::string old_nick;
        std::string err_msg;

        if (!serv->get_reg().canUseNick(params[0]))
            serv->append_client_sBuff(cli, NumericReplies::nicknameInUseReply(cli->getNick(), params[0]));
        else
        {
            TargetSet   trgSet;

            old_nick = cli->getNick();
            if (!serv->get_reg_ref().setNick(cli, params[0], err_msg, &trgSet))
            {
                std::cout << RED << "[ERROR] handleNick: " << err_msg << std::endl; 
                return ;
            }
            std::string msg = ":" + old_nick + " NICK " + params[0] + "\r\n";
            serv->send_to_targetSet(trgSet, msg);
            serv->append_client_sBuff(cli, msg);
        }
        return ;
    }
    else
    {
        if (!serv->get_reg().canUseNick(params[0]))
        {
            std::string kill_msg = ":" + Server::get_server_name() + " KILL " + params[0] + " :Nick collision\r\n";
            std::string nickNameInUser_msg = ":" + Server::get_server_name() + " 433 * " + params[0] + " :Nickname is already in use\r\n";

            send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTROUTE);
            send(cli->getFd(), nickNameInUser_msg.c_str(), nickNameInUser_msg.size(), MSG_DONTWAIT);
            cli->setState(KILLED);
            return ;
        }
        std::string err_msg;
        if (!serv->get_reg_ref().setNick(cli, params[0], err_msg, NULL))
            std::cout << RED << "[ERROR] handleNick (unregistered): " << err_msg << std::endl; 
        cli->setState(WAITING_USER);
        return ;
    }
}

void CommandHandler::handleUser(Server *serv, Client *cli, const std::vector<std::string>& params){
    if (cli->getState() == REGISTERED){
        serv->append_client_sBuff(cli, NumericReplies::alreadyRegisteredReply(cli->getNick()));
        return ;
    }
    if (params.empty() || params.size() < 4 || params[0].empty()){
		std::string errMsg = NumericReplies::needMoreParamsReply("*", "USER");
  	    std::string kill_msg = ":" + Server::get_server_name() + " KILL " + ":Not enough parameter for USER\r\n";

		send(cli->getFd(), errMsg.c_str(), errMsg.size(), MSG_DONTWAIT);
		send(cli->getFd(), kill_msg.c_str(), kill_msg.size(), MSG_DONTWAIT);
		cli->setState(KILLED);
        return ;
    }
    cli->setUser(params[0]);
    cli->setHost(params[1]);
    cli->setReal(params[3]);
    serv->append_client_sBuff(cli, NumericReplies::welcomeReply(cli->getNick(), cli->getUser(), cli->getHost()));
	serv->append_client_sBuff(cli, NumericReplies::yourHostReply(cli->getNick(), Server::get_server_name(), Server::get_version()));
	serv->append_client_sBuff(cli, NumericReplies::createdReply(cli->getNick(), serv->get_str_lTime()));
	serv->append_client_sBuff(cli, NumericReplies::myInfoReply(cli->getNick(), Server::get_server_name(), Server::get_version() , "*", "*"));
    cli->setState(REGISTERED);
} 

void CommandHandler::handleJoin(Server *serv, Client *cli, const std::vector<std::string>& params, const std::string& /* nick */) 
{
    // JOIN requires at least 1 param (channel name or "0")
    if (params.empty()) 
    {
        serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "JOIN"));
        return;
    }

    // JOIN 0 means leave all channels
    if (params[0] == "0") 
    {
        // Get all channels the user is currently in and send PART for each
        const std::map<std::string, Channel*>& allChannels = serv->get_reg().getAllChannels();
        
        std::vector<Channel*> channelsToLeave; // Collect channels to leave (avoid iterator invalidation -> google that)
        
        for (std::map<std::string, Channel*>::const_iterator it = allChannels.begin(); 
             it != allChannels.end(); ++it) 
        {
            Channel* channel = it->second;
            if (channel && channel->has(cli)) 
                channelsToLeave.push_back(channel);
        }
        
        // Send PART message for each channel the user was in
        for (std::vector<Channel*>::iterator it = channelsToLeave.begin(); 
             it != channelsToLeave.end(); ++it) 
        {
            Channel* channel = *it;
            
            // Create PART message: ":nick PART #channel :Leaving all channels"
            std::string partMsg = ":" + cli->getNick() + " PART " + channel->getName() + " :Leaving all channels\r\n";
            
            // Send PART message to all members of the channel (including the leaving user)
            const std::set<Client*>& members = channel->getMembers();
            for (std::set<Client*>::const_iterator memberIt = members.begin(); 
                 memberIt != members.end(); ++memberIt) 
            {
                Client* member = *memberIt;
                if (member) {
                    serv->append_client_sBuff(member, partMsg);
                }
            }
            
            channel->removeMember(cli);
            //add something to delete empty channels ?
        }
        return;
    }

    // Parse channel list (#chan1,#chan2,#chan3,...)
    std::string channelList = params[0];
    std::vector<std::string> channels = splitTargets(channelList);
    
    // Parse optional key list (key1,key2,key3,...)
    std::vector<std::string> keys;
    if (params.size() > 1)
        keys = splitTargets(params[1]);
    
    for (size_t i = 0; i < channels.size(); ++i) 
    {
        std::string channelName = channels[i];
        
        // Remove any leading/trailing whitespace from channel name
        size_t start = channelName.find_first_not_of(" \t");
        size_t end = channelName.find_last_not_of(" \t");
        
        if (start == std::string::npos)
            continue; // Skip empty channel names
        
        channelName = channelName.substr(start, end - start + 1);
        
        // Validate channel name format
        bool invalidName = false;
        if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&')) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        if (channelName.length() > 50) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        for (size_t j = 0; j < channelName.length(); ++j) 
        {
            char c = channelName[j];
            if (c == ' ' || c == ',' || c < 32 || c == 127) {
                invalidName = true;
                break;
            }
        }
        
        if (invalidName) {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        // Get the corresponding key for this channel (if provided)
        std::string channelKey = "";
        if (i < keys.size()) 
        {
            channelKey = keys[i];
            // Remove whitespace from key
            size_t keyStart = channelKey.find_first_not_of(" \t");
            size_t keyEnd = channelKey.find_last_not_of(" \t");
            if (keyStart != std::string::npos) {
                channelKey = channelKey.substr(keyStart, keyEnd - keyStart + 1);
            }
        }
        
        // Try to find existing channel or create new one with joinChannel (thx Mervan le goat)
        std::string joinError;
        TargetSet notifyTargets;
        
        bool joinSuccess = serv->get_reg_ref().joinChannel(cli, channelName, channelKey, joinError, notifyTargets);
        
        if (!joinSuccess) 
        {
            if (joinError.find("key") != std::string::npos)
                serv->append_client_sBuff(cli, NumericReplies::badChannelKeyReply(cli->getNick(), channelName));
            else if (joinError.find("full") != std::string::npos)
                serv->append_client_sBuff(cli, NumericReplies::channelIsFullReply(cli->getNick(), channelName));
            else if (joinError.find("invite") != std::string::npos)
                serv->append_client_sBuff(cli, NumericReplies::inviteOnlyChannelReply(cli->getNick(), channelName));
            else if (joinError.find("banned") != std::string::npos)
                serv->append_client_sBuff(cli, NumericReplies::bannedFromChannelReply(cli->getNick(), channelName));
            else
                serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        Channel* channel = serv->get_reg().findChannel(channelName);
        if (!channel)
        {
            // safety check
            continue;
        }
        
        // Create and send JOIN message to all channel members (including the new member)
        std::string joinMsg = ":" + cli->getFullHostMask() + " JOIN " + channelName + "\r\n";
        
        for (std::vector<Client*>::iterator it = notifyTargets.users.begin(); 
             it != notifyTargets.users.end(); ++it) 
        {
            Client* member = *it;
            if (member)
                serv->append_client_sBuff(member, joinMsg);
        }
        
        // Send channel topic to the new member (if channel has a topic)
        std::string topic = channel->getTopic();
        if (!topic.empty()) 
        {
            std::string topicReply = ":" + Server::get_server_name() + " 332 " + cli->getNick() + " " + channelName + " :" + topic + "\r\n";
            serv->append_client_sBuff(cli, topicReply);
        }
        
        // Send NAMES list to the new member (shows all users in the channel)
        std::string userList = "";
        const std::set<Client*>& members = channel->getMembers();
        for (std::set<Client*>::const_iterator memberIt = members.begin(); 
             memberIt != members.end(); ++memberIt) 
        {
            Client* member = *memberIt;
            if (!member) continue;
            
            if (!userList.empty())
                userList += " ";            
            
            if (channel->isOp(member))
                userList += "@";
            
            userList += member->getNick();
        }
        
        // Send RPL_NAMREPLY (353) to the new member
        if (!userList.empty())
            serv->append_client_sBuff(cli, NumericReplies::nameReply(cli->getNick(), channelName, userList));
        
        // Send RPL_ENDOFNAMES (366) to complete the names list
        serv->append_client_sBuff(cli, NumericReplies::endOfNamesReply(cli->getNick(), channelName));
    }
}

void CommandHandler::handlePart(Server *serv, Client *cli, const std::vector<std::string>& params, const std::string& /* nick */) 
{
    if (params.empty()) 
    {
        serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "PART"));
        return;
    }

    // Parse channel list
    std::string channelList = params[0];
    std::vector<std::string> channels = splitTargets(channelList);
    
    // Parse optional part message
    std::string partMessage = "";
    if (params.size() > 1) 
    {
        partMessage = params[1];
        
        // Remove leading colon if present
        if (!partMessage.empty() && partMessage[0] == ':') 
            partMessage = partMessage.substr(1);
    }
    
    if (partMessage.empty())
        partMessage = cli->getNick(); // Default IRC part message is just the nickname

    // Process each channel in the list
    for (size_t i = 0; i < channels.size(); ++i) 
    {
        std::string channelName = channels[i];
        
        // Remove any leading/trailing whitespace from channel name
        size_t start = channelName.find_first_not_of(" \t");
        size_t end = channelName.find_last_not_of(" \t");
        
        if (start == std::string::npos)
            continue;
        
        channelName = channelName.substr(start, end - start + 1);

        //check channel format and existence
        if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&')) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        Channel* channel = serv->get_reg().findChannel(channelName);
        if (!channel) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        // Check if user is actually in the channel
        if (!channel->has(cli)) 
        {
            serv->append_client_sBuff(cli, NumericReplies::notOnChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        // Use Registry's partChannel (Mervan le goat once again)
        std::string partError;
        TargetSet notifyTargets;
        
        bool partSuccess = serv->get_reg_ref().partChannel(cli, channelName, partError, notifyTargets);
        
        if (!partSuccess) 
        {
            if (partError.find("not on channel") != std::string::npos)
                serv->append_client_sBuff(cli, NumericReplies::notOnChannelReply(cli->getNick(), channelName));
            else
                serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        // Create and send PART message to all channel members (including the leaving user)
        std::string partMsg = ":" + cli->getNick() + " PART " + channelName + " :" + partMessage + "\r\n";
        for (std::vector<Client*>::iterator it = notifyTargets.users.begin(); 
             it != notifyTargets.users.end(); ++it) 
        {
            Client* member = *it;
            if (member)
                serv->append_client_sBuff(member, partMsg);
        }

        // Pas necessaire non ? on lui envoie deja

        // // Also send to the leaving client
        // serv->append_client_sBuff(cli, partMsg);
        
        //Delete empty channels ?
    }
}

void CommandHandler::handlePrivmsg(Server *serv, Client *cli, const std::vector<std::string>& params)
{
	if (params.empty())
	{
		serv->append_client_sBuff(cli, NumericReplies::noRecipientReply(cli->getNick(), "PRIVMSG"));
		return ;
	}
	if (params.size() == 1)
	{
		serv->append_client_sBuff(cli, NumericReplies::noTextToSendReply(cli->getNick()));
		return ;
	}

	std::vector<std::string>    targets = splitTargets(params[0]);
    std::string                 msg = params[1];

	for (size_t i = 0; i < targets.size(); i++)
	{
		// If target is a channel
		if (targets[i].find('#') != std::string::npos)
		{
			std::string	chanName = targets[i].substr(targets[i].find('#')); // Important si prefix d'emmission
            Channel     *targetChan = serv->get_reg().findChannel(chanName);

			if (targetChan == NULL)
			{
				serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), chanName));
				return ;
			}
			// Prefix d'emission !!! a ajouter
            serv->send_to_channel(targetChan, cli, ":" + cli->getNick() + " PRIVMSG " + targets[i] + " :" + msg + "\r\n");
		}
		// if target is a user
		else
		{
            Client  *target = serv->get_reg().findClientByNick(targets[i]);
			if (target == NULL || !target->isRegistered())
			{
				serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), targets[i]));
				return ;
			}
			if (target->isBot())
            {
                Bot *bot = dynamic_cast<Bot *>(target);
                bot->processMsg(serv, cli, msg);
                return ;
            }
			std::string	ircMsg = ":" + cli->getNick() + " PRIVMSG " + targets[i] + " :" + msg + "\r\n";
			serv->append_client_sBuff(target, ircMsg);
		}
	}
}

// TOPIC <channel> <topic>
void CommandHandler::handleTopic(Server* serv, Client* cli, const std::vector<std::string>& params)
{
    if (params.empty())
    {
        std::string errorMsg = ":" + Server::get_server_name() + " 461 " + cli->getNick() + " TOPIC :Not enough parameters\r\n";
        serv->append_client_sBuff(cli, errorMsg);
        return;
    }
    
    std::string channelName = params[0];
    Registry& registry = serv->get_reg_ref();
    
    Channel* channel = registry.findChannel(channelName);
    if (!channel)
    {
        std::string errorMsg = ":" + Server::get_server_name() + " 403 " + cli->getNick() + " " + channelName + " :No such channel\r\n";
        serv->append_client_sBuff(cli, errorMsg);
        return;
    }
    
    if (!channel->has(cli))
    {
        std::string errorMsg = ":" + Server::get_server_name() + " 442 " + cli->getNick() + " " + channelName + " :You're not on that channel\r\n";
        serv->append_client_sBuff(cli, errorMsg);
        return;
    }
    
    // If only channel name provided, return current topic
    if (params.size() == 1)
    {
        std::string currentTopic = channel->getTopic();
        if (currentTopic.empty())
        {
            // No topic set - send RPL_NOTOPIC (331)
            std::string noTopicMsg = ":" + Server::get_server_name() + " 331 " + cli->getNick() + " " + channelName + " :No topic is set\r\n";
            serv->append_client_sBuff(cli, noTopicMsg);
        }
        else
        {
            // Topic exists - send RPL_TOPIC (332)
            std::string topicMsg = ":" + Server::get_server_name() + " 332 " + cli->getNick() + " " + channelName + " :" + currentTopic + "\r\n";
            serv->append_client_sBuff(cli, topicMsg);
        }
        return;
    }
    
    // Topic parameter provided - set new topic
    // Check topic protection mode (+t) and operator privileges
    if (channel->hasTopicProtection() && !channel->isOp(cli))
    {
        std::string errorMsg = ":" + Server::get_server_name() + " 482 " + cli->getNick() + " " + channelName + " :You're not channel operator\r\n";
        serv->append_client_sBuff(cli, errorMsg);
        return;
    }
    
    std::string newTopic;
    for (size_t i = 1; i < params.size(); i++)
    {
        if (i > 1)
            newTopic += " ";
        newTopic += params[i];
    }
    
    // Handle empty topic (clear topic)
    if (newTopic == ":" || newTopic.empty())
        newTopic = "";
    else if (newTopic[0] == ':')
        newTopic = newTopic.substr(1);
    
    // Set the new topic using Registry
    std::string error;
    TargetSet notify;
    bool success = registry.setTopic(channel, newTopic, cli, error, notify);
    if (!success)
    {
        std::string errorMsg = ":" + Server::get_server_name() + " 482 " + cli->getNick() + " " + channelName + " :" + error + "\r\n";
        serv->append_client_sBuff(cli, errorMsg);
        return;
    }
    
    // Topic set successfully - broadcast to all channel members
    std::string topicChangeMsg = ":" + cli->getNick() + "!" + cli->getUser() + "@" + cli->getHost() + 
                                 " TOPIC " + channelName + " :" + newTopic + "\r\n";
    
    // Send to all members of the channel using the notify set
    for (size_t i = 0; i < notify.users.size(); i++)
    {
        serv->append_client_sBuff(notify.users[i], topicChangeMsg);
    }
}

void CommandHandler::handleInvite(Server *serv, Client *cli, const std::vector<std::string>& params)
{
    // INVITE requires exactly 2 parameters: nickname and channel
    if (params.size() < 2)
    {
        serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "INVITE"));
        return;
    }
    
    std::string targetNick = params[0];
    std::string channelName = params[1];
    
    // Remove whitespace from parameters
    size_t start = targetNick.find_first_not_of(" \t");
    size_t end = targetNick.find_last_not_of(" \t");
    if (start != std::string::npos)
        targetNick = targetNick.substr(start, end - start + 1);
        
    start = channelName.find_first_not_of(" \t");
    end = channelName.find_last_not_of(" \t");
    if (start != std::string::npos)
        channelName = channelName.substr(start, end - start + 1);
    
    // Validate channel name format
    if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
    {
        serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
        return;
    }
    
    // Find the target user
    Client* targetClient = serv->get_reg().findClientByNick(targetNick);
    if (!targetClient || !targetClient->isRegistered())
    {
        serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), targetNick));
        return;
    }
    
    // Find the channel
    Channel* channel = serv->get_reg().findChannel(channelName);
    if (!channel)
    {
        serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
        return;
    }
    
    // Check if inviter is in the channel
    if (!channel->has(cli))
    {
        serv->append_client_sBuff(cli, NumericReplies::notOnChannelReply(cli->getNick(), channelName));
        return;
    }
    
    // Check if target is already in the channel
    if (channel->has(targetClient))
    {
        serv->append_client_sBuff(cli, NumericReplies::userOnChannelReply(cli->getNick(), targetNick, channelName));
        return;
    }
    
    // Check if channel is invite-only (+i) and inviter has operator privileges
    if (channel->hasInviteOnly() && !channel->isOp(cli))
    {
        serv->append_client_sBuff(cli, NumericReplies::channelOperatorPrivilegesNeededReply(cli->getNick(), channelName));
        return;
    }
    
    // TODO: Add invitation to target's invite list (if implementing invite lists)
    // For now, we'll just send the invite messages
    if (!channel->addInvited(targetClient))
    {
        std::string alreadyInvitedReply = ":" + Server::get_server_name() + " " + cli->getNick() + " " + targetNick + " is already invited to " + channelName + "\r\n";
        serv->append_client_sBuff(cli, alreadyInvitedReply);
        return ;
    }
    
    // Send RPL_INVITING to the inviter
    std::string invitingReply = ":" + Server::get_server_name() + " 341 " + cli->getNick() + " " + 
                               targetNick + " " + channelName + "\r\n";
    serv->append_client_sBuff(cli, invitingReply);
    
    // Send INVITE message to the target user
    std::string inviteMsg = ":" + cli->getFullHostMask() + " INVITE " + targetNick + " " + channelName + "\r\n";
    serv->append_client_sBuff(targetClient, inviteMsg);
}

// KICK <channel>,<channel>,... <user>,<user>,... <comment>
void CommandHandler::handleKick(Server *serv, Client *cli, const std::vector<std::string>& params) 
{
    if (!cli->isRegistered()) 
    {
        serv->append_client_sBuff(cli, NumericReplies::notRegisteredReply());
        return;
    }

    // KICK requires at least two parameters (channel and user)
    if (params.size() < 2) 
    {
        serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "KICK"));
        return;
    }

    // Parse channel list
    std::string channelList = params[0];
    std::vector<std::string> channels = splitTargets(channelList);
    
    // Parse user list
    std::string userList = params[1];
    std::vector<std::string> users = splitTargets(userList);
    
    // Parse kick reason
    std::string kickReason = "";
    if (params.size() > 2) 
    {
        kickReason = params[2];
        // Remove leading colon if present (IRC trailing parameter format)
        if (!kickReason.empty() && kickReason[0] == ':')
            kickReason = kickReason.substr(1);
    }
    if (kickReason.empty())
        kickReason = cli->getNick(); // Default IRC kick reason if none provided -> the kicker's nickname

    // Process each channel
    for (size_t i = 0; i < channels.size(); ++i) 
    {
        std::string channelName = channels[i];
        // Remove any leading/trailing whitespace from channel name
        size_t start = channelName.find_first_not_of(" \t");
        size_t end = channelName.find_last_not_of(" \t");
        
        if (start == std::string::npos)
            continue;    
        channelName = channelName.substr(start, end - start + 1);
        if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&')) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        Channel* channel = serv->get_reg().findChannel(channelName);
        if (!channel) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), channelName));
            continue;
        }
        
        // Check if kicker is in the channel and is OP
        if (!channel->has(cli)) 
        {
            serv->append_client_sBuff(cli, NumericReplies::notOnChannelReply(cli->getNick(), channelName));
            continue;
        }
        if (!channel->isOp(cli)) 
        {
            serv->append_client_sBuff(cli, NumericReplies::channelOperatorPrivilegesNeededReply(cli->getNick(), channelName));
            continue;
        }
        
        // Process each user to kick from this channel
        for (size_t j = 0; j < users.size(); ++j) 
        {
            std::string targetNick = users[j];
            size_t nickStart = targetNick.find_first_not_of(" \t");
            size_t nickEnd = targetNick.find_last_not_of(" \t");
            if (nickStart == std::string::npos)
                continue;
            
            targetNick = targetNick.substr(nickStart, nickEnd - nickStart + 1);
            
            // user exists
            Client* targetClient = serv->get_reg().findClientByNick(targetNick);
            if (!targetClient) 
            {
                serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), targetNick));
                continue;
            }
            // user is in the channel
            if (!channel->has(targetClient)) 
            {
                serv->append_client_sBuff(cli, NumericReplies::userNotInChannelReply(cli->getNick(), targetNick, channelName));
                continue;
            }
            
            // Prevent self-kick (?)
            if (targetClient == cli)
                continue;
            
            // Create and send KICK message to all channel members (including kicked user)
            std::string kickMsg = ":" + cli->getNick() + " KICK " + channelName + " " + targetNick + " :" + kickReason + "\r\n";
            const std::set<Client*>& members = channel->getMembers();
            for (std::set<Client*>::const_iterator it = members.begin(); it != members.end(); ++it) 
            {
                Client* member = *it;
                if (member) {
                    serv->append_client_sBuff(member, kickMsg);
                }
            }

            channel->removeMember(targetClient);
        }
    }
}

void CommandHandler::handleMode(Server *serv, Client  *cli, const std::vector<std::string>& params){
    
    if (params.empty())
    {
        serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "MODE"));
        return ;
    }

    Channel		*chan = serv->get_reg().findChannel(params[0]);
	bool		targetIsChan = params[0].find("#") != std::string::npos;

	std::cout << YELLOW << "[DEBUG] processModeBlock: Processing MODE block for target " << params[0] << RESET << std::endl;
	for(size_t i = 0; i < params.size(); i++)
		std::cout << YELLOW << "[DEBUG] processModeBlock:   Param " << i << ": " << params[i] << RESET << std::endl;

	if (!targetIsChan)
	{
		if (serv->get_reg().findClientByNick(params[0]) == NULL)
      	    serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), params[0]));
       	else if (params[0] != cli->getNick())
        	serv->append_client_sBuff(cli, NumericReplies::usersDontMatchReply(cli->getNick()));
		else
    	  	serv->append_client_sBuff(cli, ":" + Server::get_server_name() + " 501 " + cli->getNick() + " User modes not handled\r\n");
		return ;
	}
	else
	{
		if (chan == NULL)
		{
       		serv->append_client_sBuff(cli, NumericReplies::noSuchChannelReply(cli->getNick(), params[0]));
			return ;
		}
 		if (params.size() == 1)
		{
   	    	serv->append_client_sBuff(cli, NumericReplies::channelModeIsReply(cli->getNick(), chan->getName(), chan->getModeStr()));
			return ;
		}
	}
    if (!chan->isOp(cli))
    {
        serv->append_client_sBuff(cli, NumericReplies::noPrivilegesReply(cli->getNick()));
        return ;
    }

	std::string	modeString = params[1];
	bool		validModes = false;
	bool		addMode = false;
	size_t		argIndex = 2;
	std::string	modeMsg = ":" + cli->getFullHostMask() + " MODE " + chan->getName() + " ";
	std::string	addedModes;
	std::string	addedParams;

    for(size_t i = 0; i < modeString.size(); i++)
	{
        if (modeString[i] == '+' || modeString[i] == '-')
        {
            addMode = modeString[i] == '+';
			if (modeString.find_first_of("tiklo", i + 1) != std::string::npos)
				addedModes += modeString[i];
            continue;
        }
        else if (modeString[i] == 'i')
		{
            chan->setInviteOnly(addMode);
			addedModes += modeString[i];
			validModes = true;
		}
        else if (modeString[i] == 't')
		{
            chan->setTopicProtection(addMode);
			addedModes += modeString[i];
			validModes = true;
		}
        else if (modeString[i] == 'k')
        {
            if (addMode)
			{
				if (argIndex >= params.size())
				{
					serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "MODE"));
					continue ;
				}
                chan->setKey(params[argIndex++]);
				addedParams += (" *");
			}
            else if (!addMode)
			{
				if (argIndex < params.size())
					argIndex++;
                chan->clearKey();
			}
			addedModes += modeString[i];
			validModes = true;
        }
		else if (modeString[i] == 'l')
        {
            if (addMode)
            {
				if (argIndex >= params.size())
				{
					serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "MODE"));
					continue ;
				}

                std::stringstream   ss(params[argIndex]);
                long                newLimit;

                if (ss >> newLimit && newLimit < 0 && newLimit > 10000)
				{
                    serv->append_client_sBuff(cli, ":" + Server::get_server_name() + " 696 " + cli->getNick() + " :Invalid mode argument(limit)\r\n");
					continue ;
				}
                chan->setLimit(static_cast<size_t>(newLimit));
				addedParams += (" " + params[argIndex++]);
            }
        	else if (!addMode)
                chan->clearLimit();
			addedModes += modeString[i];
			validModes = true;
		}
		else if (modeString[i] == 'o')
   	    {
			if (argIndex >= params.size())
			{
				serv->append_client_sBuff(cli, NumericReplies::needMoreParamsReply(cli->getNick(), "MODE"));
				continue ;
			}

            Client  *c = serv->get_reg().findClientByNick(params[argIndex]);

	        if (!c)
			{
 	        	serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), params[argIndex - 1]));
				continue ;
			}
  	        if (addMode)
   	        {
    	    	if (chan->isOp(c))
				{
     	        	serv->append_client_sBuff(cli, ":" + Server::get_server_name() + " 696 " + cli->getNick() + " :" + c->getNick() + " is already channel operator");
					continue ;
				}
       	        chan->addOp(c);
         	}
          	else
           	{
            	if (!chan->isOp(c))
				{
             	    serv->append_client_sBuff(cli, ":" + Server::get_server_name() + " 696 " + cli->getNick() + " :" + c->getNick() + " is not channel operator");
					continue ;
				}
                chan->removeOp(c);
            }
			addedModes += modeString[i];
			addedParams += (" " + params[argIndex++]);
			validModes = true;
        }
        else
            serv->append_client_sBuff(cli, NumericReplies::formatReply(ERR_UNKNOWNMODE, cli->getNick(), ":Unknown mode"));
	}
	if (validModes)
		serv->send_to_channel(chan, NULL, modeMsg + addedModes + addedParams + "\r\n");
}

void CommandHandler::handleNames(Server *serv, Client *cli, const std::vector<std::string>& params) 
{
    //IF no parameters
    if (params.empty()) 
    {
        bool foundAnyChannel = false;
        const std::map<std::string, Channel*>& allChannels = serv->get_reg().getAllChannels();
        
        for (std::map<std::string, Channel*>::const_iterator it = allChannels.begin(); 
             it != allChannels.end(); ++it) 
        {
            Channel* channel = it->second;
            if (!channel) 
                continue;
            // Check if the client is a member of this channel
            if (channel->has(cli)) 
            {
                foundAnyChannel = true;
                std::string channelName = channel->getName();
                std::string userList = "";
                
                // Get all members from the channel
                const std::set<Client*>& members = channel->getMembers();
                
                // Build the user list for this channel
                for (std::set<Client*>::const_iterator memberIt = members.begin(); 
                     memberIt != members.end(); ++memberIt)
                {
                    Client* member = *memberIt;
                    if (!member) continue; // Safety check for null pointers
                    
                    // Add space separator between nicknames (except for the first one)
                    if (!userList.empty())
                        userList += " ";
                    
                    // Add @ prefix for channel operators
                    if (channel->isOp(member)) 
                        userList += "@";
                    // Add the member's nickname
                    userList += member->getNick();
                }
                
                if (!userList.empty())
                    serv->append_client_sBuff(cli, NumericReplies::nameReply(cli->getNick(), channelName, userList));
                
                serv->append_client_sBuff(cli, NumericReplies::endOfNamesReply(cli->getNick(), channelName));
            }
        }
        
        // If client is not in any channels, send a single end-of-names with wildcard
        if (!foundAnyChannel)
            serv->append_client_sBuff(cli, NumericReplies::endOfNamesReply(cli->getNick(), "*"));        
        return;
    }

    // IF channel(s) specified
    std::string channelList = params[0];
    std::istringstream iss(channelList);
    std::string channelName;
    
    while (std::getline(iss, channelName, ',')) 
    {
        // Remove whitespaces between channel names
        size_t start = channelName.find_first_not_of(" \t");
        size_t end = channelName.find_last_not_of(" \t");
        
        if (start == std::string::npos)
            continue; // Skip empty channel names

        channelName = channelName.substr(start, end - start + 1);
        
        // Find the channel in the server registry
        Channel* channel = serv->get_reg().findChannel(channelName);
        
        if (!channel) 
        {
            serv->append_client_sBuff(cli, NumericReplies::endOfNamesReply(cli->getNick(), channelName));
            continue;
        }
        
        std::string userList = "";
        
        if (channel->has(cli)) 
        {
            const std::set<Client*>& members = channel->getMembers();
            
            for (std::set<Client*>::const_iterator it = members.begin(); it != members.end(); ++it)
            {
                Client* member = *it;
                if (!member) 
                    continue;
                
                if (!userList.empty())
                    userList += " ";
                
                // Check if this member is a channel operator and add @ prefix
                if (channel->isOp(member))
                    userList += "@";
                userList += member->getNick();
            }
        } 
        else  //client is not in the channel(s)
        {
            userList = ""; // Empty list for non-members
        }
        
        // Send RPL_NAMREPLY (353) only if we have users to list
        if (!userList.empty()) 
        {
            // Format: :" + Server::get_server_name() + " 353 <client> <symbol> <channel> :<users>
            // Symbol meanings:
            // = : public channel (visible to everyone)
            // @ : secret channel (invisible unless you're in it)  
            // * : private channel (visible but membership is private)
            std::string symbol = "="; // Default to public channel, change later ?
            
            serv->append_client_sBuff(cli, NumericReplies::nameReply(cli->getNick(), channelName, userList));
        }
        serv->append_client_sBuff(cli, NumericReplies::endOfNamesReply(cli->getNick(), channelName));
    }
}

void CommandHandler::handleWho(Server *serv, Client *cli, const std::vector<std::string>& params) 
{
    std::string target = "*"; // Default to show all visible users
    bool operatorsOnly = false;

    // Parse parameters
    if (!params.empty()) 
    {
        target = params[0];
        
        // Check for 'o' flag in second parameter
        if (params.size() > 1 && params[1] == "o") {
            operatorsOnly = true;
        }
    }
    // Note: If no parameters are provided, target remains "*" which shows all visible users
    
    // Check if target is a channel (starts with # or &)
    if (!target.empty() && (target[0] == '#' || target[0] == '&')) 
    {
        Channel* channel = serv->get_reg().findChannel(target);
        
        if (!channel) 
        {
            std::string endOfWhoReply = ":" + Server::get_server_name() + " 315 " + cli->getNick() + " " + target + " :End of /WHO list\r\n";
            serv->append_client_sBuff(cli, endOfWhoReply);
            return;
        }
        
        // Check if client has permission to see channel members
        if (channel->has(cli)) 
        {
            // Get all members from the channel and iterate through them
            const std::set<Client*>& members = channel->getMembers();
            
            // Iterate through all channel members
            for (std::set<Client*>::const_iterator it = members.begin(); it != members.end(); ++it)
            {
                Client* member = *it;
                if (!member) 
                    continue;
                
                if (operatorsOnly && !channel->isOp(member))
                    continue;
                
                // Build flags for this member
                std::string flags = "H"; // H = Here (not away), G = Gone (away)
                
                // Add operator flag if this member is a channel operator
                if (channel->isOp(member))
                    flags += "@";

                std::string reply = ":" + Server::get_server_name() + " 352 " + cli->getNick() + " " + target + " " +
                                   member->getUser() + " " + member->getHost() + " server " +
                                   member->getNick() + " " + flags + " :0 " + member->getReal() + "\r\n";
                
                serv->append_client_sBuff(cli, reply);
            }
        }
    } 
    else         // WHO for a user pattern or all users
    {
        if (target == "*") 
        {
            // Show all users visible to the requesting client
            // In IRC, this typically means users who share at least one channel with the client
            
            std::set<Client*> visibleUsers; // Use set to avoid duplicates
            
            // Get all channels and find users who share channels with the requesting client
            const std::map<std::string, Channel*>& allChannels = serv->get_reg().getAllChannels();
            
            for (std::map<std::string, Channel*>::const_iterator chanIt = allChannels.begin(); 
                 chanIt != allChannels.end(); ++chanIt) 
            {
                Channel* channel = chanIt->second;
                if (!channel || !channel->has(cli)) continue; // Skip if client not in this channel
                
                // Add all members of channels the client is in
                const std::set<Client*>& members = channel->getMembers();
                for (std::set<Client*>::const_iterator memberIt = members.begin(); 
                     memberIt != members.end(); ++memberIt) 
                {
                    Client* member = *memberIt;
                    if (member) {
                        visibleUsers.insert(member);
                    }
                }
            }
            
            // Send WHO reply for each visible user
            for (std::set<Client*>::iterator userIt = visibleUsers.begin(); 
                 userIt != visibleUsers.end(); ++userIt) 
            {
                Client* user = *userIt;
                if (!user) continue;
                
                // Skip if operators-only mode and user is not an operator in any shared channel
                if (operatorsOnly) {
                    bool isOpInAnySharedChannel = false;
                    for (std::map<std::string, Channel*>::const_iterator chanIt = allChannels.begin(); 
                         chanIt != allChannels.end(); ++chanIt) 
                    {
                        Channel* channel = chanIt->second;
                        if (channel && channel->has(cli) && channel->has(user) && channel->isOp(user)) {
                            isOpInAnySharedChannel = true;
                            break;
                        }
                    }
                    if (!isOpInAnySharedChannel) continue;
                }
                
                std::string channelName = "*"; // Not in any specific channel context
                std::string flags = "H"; // Here (not away)
                
                std::string reply = ":" + Server::get_server_name() + " 352 " + cli->getNick() + " " + channelName + " " +
                                   user->getUser() + " " + user->getHost() + " server " +
                                   user->getNick() + " " + flags + " :0 " + user->getReal() + "\r\n";
                
                serv->append_client_sBuff(cli, reply);
            }
        }
        else 
        {
            // WHO for a specific user nickname
            Client* targetClient = serv->get_reg().findClientByNick(target);
            
            if (targetClient) 
            {
                // Check if the target user shares at least one channel with the requesting client
                bool sharesChannel = false;
                const std::map<std::string, Channel*>& allChannels = serv->get_reg().getAllChannels();
                
                for (std::map<std::string, Channel*>::const_iterator it = allChannels.begin(); 
                     it != allChannels.end(); ++it) 
                {
                    Channel* channel = it->second;
                    if (channel && channel->has(cli) && channel->has(targetClient)) 
                    {
                        sharesChannel = true;
                        break;
                    }
                }
                
                if (sharesChannel) 
                {
                    bool isOpInSharedChannel = false;
                    if (operatorsOnly) 
                    {
                        for (std::map<std::string, Channel*>::const_iterator chanIt = allChannels.begin(); 
                             chanIt != allChannels.end(); ++chanIt) 
                        {
                            Channel* channel = chanIt->second;
                            if (channel && channel->has(cli) && channel->has(targetClient) && channel->isOp(targetClient)) {
                                isOpInSharedChannel = true;
                                break;
                            }
                        }
                    }
                    
                    if (!operatorsOnly || isOpInSharedChannel) 
                    {
                        std::string channelName = "*"; // Not in specific channel context
                        std::string flags = "H"; // Here (not away)
                        
                        std::string reply = ":" + Server::get_server_name() + " 352 " + cli->getNick() + " " + channelName + " " +
                                           targetClient->getUser() + " " + targetClient->getHost() + " server " +
                                           targetClient->getNick() + " " + flags + " :0 " + targetClient->getReal() + "\r\n";
                        
                        serv->append_client_sBuff(cli, reply);
                    }
                }
            }
            // If user not found or no shared channels, no WHO reply is sent (just RPL_ENDOFWHO)
        }
    }
    
    std::string endOfWhoReply = ":" + Server::get_server_name() + " 315 " + cli->getNick() + " " + target + " :End of /WHO list\r\n";
    serv->append_client_sBuff(cli, endOfWhoReply);
}

void CommandHandler::handleWhois(Server *serv, Client *cli, const std::vector<std::string>& params) 
{
    if (params.empty()) // At least one parameter is needed
    {
        serv->append_client_sBuff(cli, NumericReplies::noNicknameGivenReply(cli->getNick()));
        return;
    }
    
    // Get the nickname list (can be comma-separated)
    std::string nicknameList = params[0];
    std::istringstream iss(nicknameList);
    std::string nickname;
    
    while (std::getline(iss, nickname, ',')) 
    {
        // Remove whitespaces
        size_t start = nickname.find_first_not_of(" \t");
        size_t end = nickname.find_last_not_of(" \t");
        
        if (start == std::string::npos)
            continue;
        
        nickname = nickname.substr(start, end - start + 1);
        
        // Find the target client by nickname
        Client* targetClient = serv->get_reg().findClientByNick(nickname);
        
        if (!targetClient) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), nickname));
            continue;
        }
        
        bool canSeeUser = false;
        const std::map<std::string, Channel*>& allChannels = serv->get_reg().getAllChannels();
        
        // Users can always WHOIS themselves
        if (targetClient == cli)
            canSeeUser = true;
        else 
        {
            // Check if requesting client and target client share any channels
            for (std::map<std::string, Channel*>::const_iterator it = allChannels.begin(); 
                 it != allChannels.end(); ++it) 
            {
                Channel* channel = it->second;
                if (channel && channel->has(cli) && channel->has(targetClient)) 
                {
                    canSeeUser = true;
                    break;
                }
            }
        }
        if (!canSeeUser) 
        {
            serv->append_client_sBuff(cli, NumericReplies::noSuchNickReply(cli->getNick(), nickname));
            continue;
        }
        // Format: :server 311 <client> <nick> <user> <host> * :<real>
        std::string whoisUserReply = ":" + Server::get_server_name() + " 311 " + cli->getNick() + " " +
                                    targetClient->getNick() + " " + targetClient->getUser() + " " +
                                    targetClient->getHost() + " * :" + targetClient->getReal() + "\r\n";
        serv->append_client_sBuff(cli, whoisUserReply);
        
        // Iterate through all channels to find which ones the target client is in
        std::string channelsList = "";
        // Reuse the allChannels variable from privacy check above
        
        // Build list of channels the target client is in
        for (std::map<std::string, Channel*>::const_iterator it = allChannels.begin(); 
             it != allChannels.end(); ++it) 
        {
            Channel* channel = it->second;
            if (!channel) 
                continue; // Safety check for null pointers
            
            // Check if target client is a member of this channel
            if (channel->has(targetClient)) 
            {
                // Only show channels that the requesting client can also see
                if (channel->has(cli)) 
                {
                    // Add space separator between channel names (except for the first one)
                    if (!channelsList.empty())
                        channelsList += " ";
                    
                    // Add @ prefix if target user is an operator in this channel
                    if (channel->isOp(targetClient)) {
                        channelsList += "@";
                    }
                    
                    // Add the channel name
                    channelsList += channel->getName();
                }
            }
        }
        
        // Send RPL_WHOISCHANNELS (319) only if the user is in any channels
        if (!channelsList.empty()) 
        {
            std::string whoisChannelsReply = ":" + Server::get_server_name() + " 319 " + cli->getNick() + " " +
                                           targetClient->getNick() + " :" + channelsList + "\r\n";
            serv->append_client_sBuff(cli, whoisChannelsReply);
        }
        
        // Format: :server 312 <client> <nick> <server> :<info>
        std::string whoisServerReply = ":" + Server::get_server_name() + " 312 " + cli->getNick() + " " +
                                      targetClient->getNick() + " " + Server::get_server_name() + " :IRC Server\r\n";
        serv->append_client_sBuff(cli, whoisServerReply);
        
        // Calculate idle time based on last activity
        time_t currentTime = time(NULL);
        time_t idleSeconds = currentTime - targetClient->getLastActivity();
        time_t signonTime = currentTime - 3600; // Placeholder - you'd store actual signon time
        
        // Convert numbers to strings using C++98 compatible method
        std::ostringstream idleStream, signonStream;
        idleStream << idleSeconds;
        signonStream << signonTime;
        
        std::string whoisIdleReply = ":" + Server::get_server_name() + " 317 " + cli->getNick() + " " +
                                    targetClient->getNick() + " " +
                                    idleStream.str() + " " +
                                    signonStream.str() +
                                    " :seconds idle, signon time\r\n";
        serv->append_client_sBuff(cli, whoisIdleReply);
        
        // Send RPL_ENDOFWHOIS (318) - End of WHOIS information
        std::string endOfWhoisReply = ":" + Server::get_server_name() + " 318 " + cli->getNick() + " " + targetClient->getNick() + " :End of /WHOIS list\r\n";
        serv->append_client_sBuff(cli, endOfWhoisReply);
    }
}

void CommandHandler::handlePing(Server *serv, Client *cli, const std::vector<std::string>& params) {
    if (params.empty() || params[0].empty()) {
        std::string reply = ":" + Server::get_server_name() + " 409 * :No origin specified\r\n";
        serv->append_client_sBuff(cli, reply); // Permet d'ajouter reply au buffer a send du client
        return;
    }
    std::string pong = ":" + Server::get_server_name() + " PONG server :" + params[0] + "\r\n";
    serv->append_client_sBuff(cli, pong);
}

void CommandHandler::handlePong(Client *cli, const std::vector<std::string>& params) {
	if (params.empty() || params[0].empty())
	{
		std::cerr << RED << "[ERROR] handlePong: token is empty" << RESET << std::endl;
		return ;
	}
	cli->touchPing(params[0]);
	cli->setPingToken("");
}

void CommandHandler::handleQuit(Server *serv, Client *cli, const std::vector<std::string>& params){
    std::string message = ":" + cli->getNick() + " QUIT " + ":" + params[0] + "\r\n";
    std::map<std::string, Channel *> chanMap = serv->get_reg().getAllChannels();

    for(std::map<std::string, Channel *>::iterator it = chanMap.begin(); it != chanMap.end(); it++)
    {
        if (it->second->has(cli))
            serv->send_to_channel(it->second, cli, message);
    }
    cli->setState(QUIT);
}

void CommandHandler::handleUnknownCommand(Server *serv, Client *cli, const std::string& command) {
    std::string reply = ":" + Server::get_server_name() + " 421 * " + command + " :Unknown command\r\n";
    serv->append_client_sBuff(cli, reply);
}
