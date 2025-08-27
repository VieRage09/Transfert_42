#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>

#define BUFFER_SIZE 256

int	main()
{
	char		buffer[BUFFER_SIZE];
	std::string	tmp;
	std::string	line;
	int			size;
	int			fd;

	memset((void *)buffer, 0, sizeof(buffer));
	fd = open("test/test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("[ERROR] :");
		return (1);
	}

	while (1) // Boucle recv
	{
		size = read(fd, buffer, BUFFER_SIZE);
		std::cout << "You typed in: " << buffer << std::endl;
		tmp += buffer;
		std::cout << "Tmp = " << tmp << std::endl;
		while (!tmp.empty())
		{
			if (tmp.find_first_of("\r\n") != std::string::npos) // il y a au moins 1 \r\n dans le buffer
			{
				if (tmp.find_first_of("\r\n") == tmp.size() - 1) // Il y en a qu'un et il est a la fin
				{
					line += tmp;
					std::cout << "Executing: " << line << std::endl;
					line.clear();
					tmp.clear(); // --> On sort de la boucle
				}
				else	// Il y en a au moins un avant la fin 
				{
					line += tmp.substr(0, tmp.find_first_of("\r\n"));
					std::cout << "Executing: " << line << std::endl;
					line.clear();
					tmp = tmp.substr(tmp.find_first_of("\r\n") + 1, tmp.size());
				}
			}
			else
			{
				line += tmp;
				tmp.clear();
			}
		}
		std::cout << "========== New read ==========\n";
	}
}