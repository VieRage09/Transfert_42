/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_special.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:55:40 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/25 22:56:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use ft_strjoin on s1 and s2 then free them before returning the joined string
static char	*lucas_safe_hd(char *s1, char *s2)
{
	char	*lucas;

	lucas = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!lucas)
		return (NULL);
	return (lucas);
}

// Reset buff with only \0
static void	mehdi_clear(char *buff)
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
static int	bnchr(char *s)
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
static int	shift_buff(char *buff, int index)
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

// Boucle de lecture: cree la ligne a renvoyer puis indique ce qu'il s'est passe
// Valeurs de retour =
// -1 error
// 0 fin du fichier
// 1 line created --> success
static int	get_line(int fd, char *buff, char **line)
{
	int	check_read;

	check_read = -2;
	while (g_heredoc)
	{
		if (buff[0] == '\0')
			check_read = read(fd, buff, BUFFER_SIZE);
		if (check_read == -1)
			return (-1);
		if (bnchr(buff) != -1)
		{
			*line = lucas_safe_hd(*line, ft_substr(buff, 0, bnchr(buff) + 1));
			shift_buff(buff, bnchr(buff));
			return (1);
		}
		*line = lucas_safe_hd(*line, ft_substr(buff, 0, BUFFER_SIZE));
		mehdi_clear(buff);
		if (check_read < BUFFER_SIZE && check_read > -1)
		{
			if (check_read == 0 && *line[0] == '\0')
				return (0);
			else
				return (1);
		}
	}
	return (-1);
}

// Makes security checks and split the way between the different cases
// Returns the next line of the read file on success, NULL on failure
char	*get_next_line_hd(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			check;

	if (fd < 0 || read(fd, 0, 0) != 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	check = get_line(fd, buff, &line);
	if (!line)
		return (NULL);
	if (check <= 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}