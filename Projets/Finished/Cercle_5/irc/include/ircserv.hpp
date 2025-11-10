#ifndef IRCSERV_HPP
 #define IRCSERV_HPP

//=================================================== Project Defines ========//
#define SERV_NAME	"When_Chatting"
#define VERSION		"1.0"


#define BUFFER_SIZE	512
#define MAX_CLIENT	256
#define POLL_TO		60000	// 1 min
#define ACTIVITY_TO	300000	// [5min]
#define PING_TO		120000	// [120s]
#define RGSTR_TO	30000	// 30 sec
//============================================================================//

//===================================================== Color Defines ========//
#define RESET "\e[0m"
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[93m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[96m"
#define WHITE "\e[97m"
//============================================================================//

#endif