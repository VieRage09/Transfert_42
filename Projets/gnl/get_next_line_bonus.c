/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:55:40 by tlebon            #+#    #+#             */
/*   Updated: 2024/01/18 14:45:07by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Reset buff with only \0
void	mehdi_clear(char *buff)
{
	int	i;

	if (buff[0] == '\0')
		return ;
	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buff[i] = '\0';
		i++;
	}
}

// Return the index of the first \n encountered in buff, -1 if there is no \n
int	find_bslash_n(char *s)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// Shifts buff to the left index times en gros
int	shift_buff(char *buff, int index)
{
	int	i;

	i = 0;
	if (index < BUFFER_SIZE - 1)
	{
		index++;
		while (index + i < BUFFER_SIZE)
		{
			buff[i] = buff[index + i];
			buff[index + i] = '\0';
			i++;
		}
	}
	while (i < BUFFER_SIZE)
	{
		buff[i] = '\0';
		i++;
	}
	return (0);
}

// Boucle de lecture : cree la ligne a renvoyer puis indique ce qu il s est passe
// Valeurs de retour =
// -1 error
// 0 fin du fichier
// 1 line created --> success
int	get_line(int fd, char *buff, char **line)
{
	int check_read; //receive read() value

	check_read = -2;
	while(1)
	{
		if (buff[0] == '\0') // aka buff is empty
			check_read = read(fd, buff, BUFFER_SIZE);
		if (check_read == -1)
			return (-1);
		if (find_bslash_n(buff) != -1) // We found a \n inside buff
		{
			*line = lucas_safe(*line, ft_substr(buff, 0, find_bslash_n(buff) + 1));
			shift_buff(buff, find_bslash_n(buff));
			return (1);
		}
		*line = lucas_safe(*line, ft_substr(buff, 0, BUFFER_SIZE)); // ajoute potentiellement un \0 derriere un autre \0
		mehdi_clear(buff);
		if (check_read < BUFFER_SIZE && check_read > -1) // ??? && checkread > -1 ???
		{
			if (check_read == 0 && *line[0] == '\0') // Means read read nothing at all
				return (0);
			else				// Means read reached the end of the file
				return (1);
		}
	}
}

// Makes security checks and split the way between the different cases
// Returns the next line of the read file on success, NULL on failure
char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE + 1];
	char	*line;
	int		check;

	if (fd < 0 || read(fd, 0, 0) != 0 || BUFFER_SIZE == 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	check = get_line(fd, buff[fd], &line);
	if (!line)
		return (NULL);
	if (check == -1)
	{
		free(line);
		return (NULL);
	}
	if (check == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
