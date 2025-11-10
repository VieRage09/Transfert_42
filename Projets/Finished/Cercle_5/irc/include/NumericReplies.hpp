/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:36:45 by lberne            #+#    #+#             */
/*   Updated: 2025/10/03 17:46:07 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

#include <string>

// Success replies (001-099)
#define RPL_WELCOME             "001"
#define RPL_YOURHOST            "002"
#define RPL_CREATED             "003"
#define RPL_MYINFO              "004"
#define RPL_BOUNCE              "005"

// User/Channel information replies (200-399)
#define RPL_USERHOST            "302"
#define RPL_ISON                "303"
#define RPL_AWAY                "301"
#define RPL_UNAWAY              "305"
#define RPL_NOWAWAY             "306"
#define RPL_WHOISUSER           "311"
#define RPL_WHOISSERVER         "312"
#define RPL_WHOISOPERATOR       "313"
#define RPL_WHOISIDLE           "317"
#define RPL_ENDOFWHOIS          "318"
#define RPL_WHOISCHANNELS       "319"
#define RPL_WHOWASUSER          "314"
#define RPL_ENDOFWHOWAS         "369"
#define RPL_LISTSTART           "321"
#define RPL_LIST                "322"
#define RPL_LISTEND             "323"
#define RPL_CHANNELMODEIS       "324"
#define RPL_UNIQOPIS            "325"
#define RPL_NOTOPIC             "331"
#define RPL_TOPIC               "332"
#define RPL_INVITING            "341"
#define RPL_SUMMONING           "342"
#define RPL_INVITELIST          "346"
#define RPL_ENDOFINVITELIST     "347"
#define RPL_EXCEPTLIST          "348"
#define RPL_ENDOFEXCEPTLIST     "349"
#define RPL_VERSION             "351"
#define RPL_WHOREPLY            "352"
#define RPL_ENDOFWHO            "315"
#define RPL_NAMREPLY            "353"
#define RPL_ENDOFNAMES          "366"
#define RPL_LINKS               "364"
#define RPL_ENDOFLINKS          "365"
#define RPL_BANLIST             "367"
#define RPL_ENDOFBANLIST        "368"
#define RPL_INFO                "371"
#define RPL_ENDOFINFO           "374"
#define RPL_MOTDSTART           "375"
#define RPL_MOTD                "372"
#define RPL_ENDOFMOTD           "376"
#define RPL_YOUREOPER           "381"
#define RPL_REHASHING           "382"
#define RPL_YOURESERVICE        "383"
#define RPL_TIME                "391"
#define RPL_USERSSTART          "392"
#define RPL_USERS               "393"
#define RPL_ENDOFUSERS          "394"
#define RPL_NOUSERS             "395"

// Error replies (400-599)
#define ERR_NOSUCHNICK          "401"
#define ERR_NOSUCHSERVER        "402"
#define ERR_NOSUCHCHANNEL       "403"
#define ERR_CANNOTSENDTOCHAN    "404"
#define ERR_TOOMANYCHANNELS     "405"
#define ERR_WASNOSUCHNICK       "406"
#define ERR_TOOMANYTARGETS      "407"
#define ERR_NOSUCHSERVICE       "408"
#define ERR_NOORIGIN            "409"
#define ERR_NORECIPIENT         "411"
#define ERR_NOTEXTTOSEND        "412"
#define ERR_NOTOPLEVEL          "413"
#define ERR_WILDTOPLEVEL        "414"
#define ERR_BADMASK             "415"
#define ERR_UNKNOWNCOMMAND      "421"
#define ERR_NOMOTD              "422"
#define ERR_NOADMININFO         "423"
#define ERR_FILEERROR           "424"
#define ERR_NONICKNAMEGIVEN     "431"
#define ERR_ERRONEUSNICKNAME    "432"
#define ERR_NICKNAMEINUSE       "433"
#define ERR_NICKCOLLISION       "436"
#define ERR_UNAVAILRESOURCE     "437"
#define ERR_USERNOTINCHANNEL    "441"
#define ERR_NOTONCHANNEL        "442"
#define ERR_USERONCHANNEL       "443"
#define ERR_NOLOGIN             "444"
#define ERR_SUMMONDISABLED      "445"
#define ERR_USERSDISABLED       "446"
#define ERR_NOTREGISTERED       "451"
#define ERR_NEEDMOREPARAMS      "461"
#define ERR_ALREADYREGISTRED    "462"
#define ERR_NOPERMFORHOST       "463"
#define ERR_PASSWDMISMATCH      "464"
#define ERR_YOUREBANNEDCREEP    "465"
#define ERR_YOUWILLBEBANNED     "466"
#define ERR_KEYSET              "467"
#define ERR_CHANNELISFULL       "471"
#define ERR_UNKNOWNMODE         "472"
#define ERR_INVITEONLYCHAN      "473"
#define ERR_BANNEDFROMCHAN      "474"
#define ERR_BADCHANNELKEY       "475"
#define ERR_BADCHANMASK         "476"
#define ERR_NOCHANMODES         "477"
#define ERR_BANLISTFULL         "478"
#define ERR_NOPRIVILEGES        "481"
#define ERR_CHANOPRIVSNEEDED    "482"
#define ERR_CANTKILLSERVER      "483"
#define ERR_RESTRICTED          "484"
#define ERR_UNIQOPPRIVSNEEDED   "485"
#define ERR_NOOPERHOST          "491"
#define ERR_UMODEUNKNOWNFLAG    "501"
#define ERR_USERSDONTMATCH      "502"

// Reserved numerics
#define RPL_UMODEIS             "221"
#define RPL_SERVICEINFO         "231"
#define RPL_ENDOFSERVICES       "232"
#define RPL_SERVICE             "233"
#define RPL_SERVLIST            "234"
#define RPL_SERVLISTEND         "235"
#define RPL_STATSLINKINFO       "211"
#define RPL_STATSCOMMANDS       "212"
#define RPL_ENDOFSTATS          "219"
#define RPL_STATSPLINE          "217"
#define RPL_STATSQLINE          "222"
#define RPL_STATSYLINE          "218"
#define RPL_STATSILINE          "215"
#define RPL_STATSKLINE          "216"
#define RPL_STATSOLINE          "243"
#define RPL_STATSHLINE          "244"

namespace NumericReplies 
{
    // Formatting functions
    std::string formatReply(const std::string& code, const std::string& client, const std::string& message);
	std::string formatChannelReply(const std::string& code, const std::string& client, const std::string& channel, const std::string& message);
	    
	//common replies
    std::string welcomeReply(const std::string& nick, const std::string& user, const std::string& host);
    std::string yourHostReply(const std::string& nick, const std::string& servername, const std::string& version);
    std::string createdReply(const std::string& nick, const std::string& date);
    std::string myInfoReply(const std::string& nick, const std::string& servername, const std::string& version, const std::string& userModes, const std::string& chanModes);
    std::string motdStartReply(const std::string& nick, const std::string& servername);
    std::string motdReply(const std::string& nick, const std::string& text);
    std::string endOfMotdReply(const std::string& nick);
    
    // error replies
    std::string noSuchNickReply(const std::string& nick, const std::string& target);
    std::string noSuchChannelReply(const std::string& nick, const std::string& channel);
    std::string cannotSendToChanReply(const std::string& nick, const std::string& channel);
    std::string noRecipientReply(const std::string& nick, std::string cmd);
    std::string noTextToSendReply(const std::string& nick);
    std::string unknownCommandReply(const std::string& nick, const std::string& command);
    std::string noNicknameGivenReply(const std::string& nick);
    std::string erroneousNicknameReply(const std::string& nick, const std::string& badNick);
    std::string nicknameInUseReply(const std::string& nick, const std::string& usedNick);
    std::string nickCollisionReply(const std::string& currentNick, const std::string& collisionNick);
    std::string userNotInChannelReply(const std::string& nick, const std::string& target, const std::string& channel);
    std::string notOnChannelReply(const std::string& nick, const std::string& channel);
    std::string userOnChannelReply(const std::string& nick, const std::string& target, const std::string& channel);
    std::string notRegisteredReply();
    std::string needMoreParamsReply(const std::string& nick, const std::string& command);
    std::string alreadyRegisteredReply(const std::string& nick);
    std::string passwordMismatchReply();
    std::string channelIsFullReply(const std::string& nick, const std::string& channel);
    std::string inviteOnlyChannelReply(const std::string& nick, const std::string& channel);
    std::string bannedFromChannelReply(const std::string& nick, const std::string& channel);
    std::string badChannelKeyReply(const std::string& nick, const std::string& channel);
    std::string channelOperatorPrivilegesNeededReply(const std::string& nick, const std::string& channel);
    std::string noPrivilegesReply(const std::string& nick);
    std::string usersDontMatchReply(const std::string& nick);
    
    // channel-related replies
    std::string topicReply(const std::string& nick, const std::string& channel, const std::string& topic);
    std::string noTopicReply(const std::string& nick, const std::string& channel);
    std::string nameReply(const std::string& nick, const std::string& channel, const std::string& names);
    std::string endOfNamesReply(const std::string& nick, const std::string& channel);
    std::string invitingReply(const std::string& nick, const std::string& target, const std::string& channel);
    std::string channelModeIsReply(const std::string& nick, const std::string& channel, const std::string& modes);
    
    // User-related
    std::string uModeIsReplay(const std::string& nick, const std::string& modes);
}

#endif
