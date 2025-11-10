/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:36:35 by lberne            #+#    #+#             */
/*   Updated: 2025/10/20 19:19:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ircserv.hpp"
#include "NumericReplies.hpp"
#include "Server.hpp"

#include <sstream>

namespace NumericReplies 
{
    // Format a basic numeric reply : ":server code client message"
    std::string formatReply(const std::string& code, const std::string& client, const std::string& message) 
	{
        std::ostringstream oss;
        oss << ":" << Server::get_server_name() << " " << code << " " << client << " " << message << "\r\n";
        return oss.str();
    }

    // Format a channel-specific numeric reply : ":server code client channel :message"
    std::string formatChannelReply(const std::string& code, const std::string& client, const std::string& channel, const std::string& message) 
	{
        std::ostringstream oss;
        oss << ":" << Server::get_server_name() << " " << code << " " << client << " " << channel << " :" << message << "\r\n";
        return oss.str();
    }

    // common replies
    std::string welcomeReply(const std::string& nick, const std::string& user, const std::string& host) 
	{
        std::ostringstream oss;
        oss << ":Welcome to the Internet Relay Network " << nick << "!" << user << "@" << host;
        return formatReply(RPL_WELCOME, nick, oss.str());
    }

    std::string yourHostReply(const std::string& nick, const std::string& servername, const std::string& version) 
	{
        std::ostringstream oss;
        oss << ":Your host is " << servername << ", running version " << version;
        return formatReply(RPL_YOURHOST, nick, oss.str());
    }

    std::string createdReply(const std::string& nick, const std::string& date) {
        std::ostringstream oss;
        oss << ":This server was created " << date;
        return formatReply(RPL_CREATED, nick, oss.str());
    }

    std::string myInfoReply(const std::string& nick, const std::string& servername, const std::string& version, const std::string& userModes, const std::string& chanModes) {
        std::ostringstream oss;
        oss << servername << " " << version << " " << userModes << " " << chanModes;
        return formatReply(RPL_MYINFO, nick, oss.str());
    }

    std::string motdStartReply(const std::string& nick, const std::string& servername) {
        std::ostringstream oss;
        oss << ":- " << servername << " Message of the day - ";
        return formatReply(RPL_MOTDSTART, nick, oss.str());
    }

    std::string motdReply(const std::string& nick, const std::string& text) {
        std::ostringstream oss;
        oss << ":- " << text;
        return formatReply(RPL_MOTD, nick, oss.str());
    }

    std::string endOfMotdReply(const std::string& nick) {
        return formatReply(RPL_ENDOFMOTD, nick, ":End of MOTD command");
    }


	// errors replies
    std::string noSuchNickReply(const std::string& nick, const std::string& target) {
        std::ostringstream oss;
        oss << target << " :No such nick/channel";
        return formatReply(ERR_NOSUCHNICK, nick, oss.str());
    }

    std::string noSuchChannelReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :No such channel";
        return formatReply(ERR_NOSUCHCHANNEL, nick, oss.str());
    }

    std::string cannotSendToChanReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :Cannot send to channel";
        return formatReply(ERR_CANNOTSENDTOCHAN, nick, oss.str());
    }

    std::string noRecipientReply(const std::string& nick, std::string cmd) {
        std::ostringstream oss;
        oss << ":No recipient given " << cmd;
        return formatReply(ERR_NORECIPIENT, nick, oss.str()); 
    }

    std::string noTextToSendReply(const std::string& nick) {
        return formatReply(ERR_NOTEXTTOSEND, nick, ":No text to send");
    }

    std::string unknownCommandReply(const std::string& nick, const std::string& command) {
        std::ostringstream oss;
        oss << command << " :Unknown command";
        return formatReply(ERR_UNKNOWNCOMMAND, nick, oss.str());
    }

    std::string noNicknameGivenReply(const std::string& nick) {
        return formatReply(ERR_NONICKNAMEGIVEN, nick, ":No nickname given");
    }

    std::string erroneousNicknameReply(const std::string& nick, const std::string& badNick) {
        std::ostringstream oss;
        oss << badNick << " :Erroneous nickname";
        return formatReply(ERR_ERRONEUSNICKNAME, nick, oss.str());
    }

    std::string nicknameInUseReply(const std::string& nick, const std::string& usedNick) {
        std::ostringstream oss;
        oss << usedNick << " :Nickname is already in use";
        return formatReply(ERR_NICKNAMEINUSE, nick, oss.str());
    }

    std::string nickCollisionReply(const std::string& currentNick, const std::string& collisionNick){
        std::ostringstream oss;
        oss << collisionNick << " :Nickname collision KILL";
        return formatReply(ERR_NICKCOLLISION, currentNick, oss.str());
    }
    
    std::string userNotInChannelReply(const std::string& nick, const std::string& target, const std::string& channel) {
        std::ostringstream oss;
        oss << target << " " << channel << " :They aren't on that channel";
        return formatReply(ERR_USERNOTINCHANNEL, nick, oss.str());
    }

    std::string notOnChannelReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :You're not on that channel";
        return formatReply(ERR_NOTONCHANNEL, nick, oss.str());
    }

    std::string userOnChannelReply(const std::string& nick, const std::string& target, const std::string& channel) {
        std::ostringstream oss;
        oss << target << " " << channel << " :is already on channel";
        return formatReply(ERR_USERONCHANNEL, nick, oss.str());
    }

    std::string notRegisteredReply() {
        return formatReply(ERR_NOTREGISTERED, "*", ":You have not registered");
    }

    std::string needMoreParamsReply(const std::string& nick, const std::string& command) {
        std::ostringstream oss;
        oss << command << " :Not enough parameters";
        return formatReply(ERR_NEEDMOREPARAMS, nick, oss.str());
    }

    std::string alreadyRegisteredReply(const std::string& nick) {
        return formatReply(ERR_ALREADYREGISTRED, nick, ":Unauthorized command (already registered)");
    }

    std::string passwordMismatchReply() {
        return formatReply(ERR_PASSWDMISMATCH, "*", ":Password incorrect");
    }

    std::string channelIsFullReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :Cannot join channel (+l)";
        return formatReply(ERR_CHANNELISFULL, nick, oss.str());
    }

    std::string inviteOnlyChannelReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :Cannot join channel (+i)";
        return formatReply(ERR_INVITEONLYCHAN, nick, oss.str());
    }

    std::string bannedFromChannelReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :Cannot join channel (+b)";
        return formatReply(ERR_BANNEDFROMCHAN, nick, oss.str());
    }

    std::string badChannelKeyReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :Cannot join channel (+k)";
        return formatReply(ERR_BADCHANNELKEY, nick, oss.str());
    }

    std::string channelOperatorPrivilegesNeededReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :You're not channel operator";
        return formatReply(ERR_CHANOPRIVSNEEDED, nick, oss.str());
    }

    std::string noPrivilegesReply(const std::string& nick) {
        return formatReply(ERR_NOPRIVILEGES, nick, ":Permission Denied- You're not an IRC operator");
    }

    std::string usersDontMatchReply(const std::string& nick) {
        return formatReply(ERR_USERSDONTMATCH, nick, ":Can't change mode for other users");
    }

	// channel-related replies
    std::string topicReply(const std::string& nick, const std::string& channel, const std::string& topic) {
        return formatChannelReply(RPL_TOPIC, nick, channel, topic);
    }

    std::string noTopicReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :No topic is set";
        return formatReply(RPL_NOTOPIC, nick, oss.str());
    }

    std::string nameReply(const std::string& nick, const std::string& channel, const std::string& names) {
        std::ostringstream oss;
        oss << "= " << channel << " :" << names;
        return formatReply(RPL_NAMREPLY, nick, oss.str());
    }

    std::string endOfNamesReply(const std::string& nick, const std::string& channel) {
        std::ostringstream oss;
        oss << channel << " :End of NAMES list";
        return formatReply(RPL_ENDOFNAMES, nick, oss.str());
    }

    std::string invitingReply(const std::string& nick, const std::string& target, const std::string& channel) {
        std::ostringstream oss;
        oss << target << " " << channel;
        return formatReply(RPL_INVITING, nick, oss.str());
    }

    std::string channelModeIsReply(const std::string& nick, const std::string& channel, const std::string& modes) {
        std::ostringstream oss;
        oss << channel << " " << modes;
        return formatReply(RPL_CHANNELMODEIS, nick, oss.str());
    }

    std::string uModeIsReplay(const std::string& nick, const std::string& modes) {
        return formatReply(RPL_UMODEIS, nick, modes);
    }

}
