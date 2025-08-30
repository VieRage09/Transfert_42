#ifndef IRCSERV_HPP
 #define IRCSERV_HPP

// Defines //

#define BUFFER_SIZE 256

#define RESET "\e[0m"		// clears all colors and styles (to white on black)
#define BLACK "\e[30m"		//set foreground color to black
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"

// Includes //
#include "Server.hpp"
#include "Client.hpp"

// A recheck
#include <stdlib.h>
#include <errno.h>

#endif