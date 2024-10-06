/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:14:16 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/06 13:24:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Checks for existence and readability of the infile in argument
// If it exists and is readable, opens it and returns the fd 
// Returns -1 on failure
int	open_infile(char *file_path)
{
	int	fd;

	if (!file_path)
		return (-1);
	if (!access(file_path, F_OK) && !access(file_path, R_OK))
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			perror("Open failed");
			return (-1);
		}
	}
	else
	{
		perror("Access failed");
		return (-1);
	}
	return (fd);
}

// Checks if the outfile in argument exists and is writable
// If it doesn't exist, or if it exists and is writable 
// Opens it and returns the fd
// Uses O_APPEND Flag when append bool is set up to 1
// Return -1 on failure
int	open_outfile(char *file_path, int append)
{
	int	fd;

	if (!file_path)
		return (-1);
	if (access(file_path, F_OK) == -1)
		fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	else
	{
		if (access(file_path, W_OK) == -1)
		{
			perror("Access failed");
			return (-1);
		}
		else if (append == 1)
		{
			fd = open(file_path, O_WRONLY | O_APPEND);
			printf ("append 1\n");
		}
		else
			fd = open(file_path, O_WRONLY | O_TRUNC);
	}
	if (fd == -1)
		perror("Open failed");
	return (fd);
}

// A partir d'une commande (string entre le debut et un pipe, 
// un pipe et la fin ou 2 pipes), renvoie le fd a utiliser comme input
int	get_fdin(char **cmd_tab, int position, char **prompt_tab)
{
	int		i;
	char	*infile_path;

	i = 0;
	while (cmd_tab[i])
	{
		if (is_input_redirector(cmd_tab[i]) && cmd_tab[i + 1])
			return (open_infile(cmd_tab[i + 1]));
		// TODO : Mettre en place le heredoc
		i++;
	}
	if (position > 0 && is_pipe(prompt_tab[position - 1]))
		return (0); // entree read du pipe d'avant
	return (0);
}

int	get_fdout(char **cmd_tab, int position, char **prompt_tab)
{
	int		i;
	char	*outfile_path;

	i = 0;
	while (cmd_tab[i])
	{
		if (is_output_redirector(cmd_tab[i]) && cmd_tab[i + 1])
			return (open_outfile(cmd_tab[i + 1], 0));
		i++;
	}
	if (prompt_tab[position + 1] && is_pipe(prompt_tab[position + 1]))
		return (1); // entree write du pipe d'apres
	return (1);
}