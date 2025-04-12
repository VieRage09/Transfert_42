#include <iostream>
#include <ctime>
#include <stdbool.h>
#include <string>
#include "../headers/Intervention.hpp"



// void	harvest_intervention

int	main()
{

	time_t	ts = time(NULL);
	struct tm	date = *localtime(&ts);
	Intervention	i;

	std::cout << i;
}