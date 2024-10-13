/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:14:16 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/13 05:30:55 by tlebon           ###   ########.fr       */
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

// Iterates through s_token until it finds a pipe token or end of list
// If a R_IN is encountered, open the next arg and returns its fd
// If no R_IN is encountered, but there is a pipe before the searching area
// returns the fd of the WRITE end of pipefd
// Returns STDIN if nothing above happens
// TODO : handle heredoc
int find_fdin(t_token *s_token, int *rdpipe)
{
	t_token *curs;

	curs = s_token;
	while (curs && curs->type != PIPE)
	{
		if (curs->type == R_IN && curs->next && curs->next->type == ARG)
			return (open_infile(curs->next->str));
		curs = curs->next;
	}
	if (s_token->prev && s_token->prev->type == PIPE)
	{
	printf("rdpipe returned as fdin\n");
		// Envoyer le fd du pipefd[2], entree READ;
		return (*rdpipe);
	}
	return (STDIN_FILENO);
}

// Iterates through s_token until it finds a pipe token or end of list
// If a R_OUT of R_OUT_APPEND is encountered
// opens the next arg in append mode or not and returns its fd
// If no R_OUT nor R_OUT_APPEND is encountered, but there is a pipe
// returns the fd of the WRITE end of pipefd
// Returns STDOUT if nothing above happens
int find_fdout(t_token *s_token, int *pipefd)
{
	t_token *curs;

	curs = s_token;
	while (curs && curs->type != PIPE)
	{
		if (curs->type == R_OUT && curs->next && curs->next->type == ARG)
			return (open_outfile(curs->next->str, 0));
		if (curs->type == R_OUT_APPEND && curs->next && curs->next->type == ARG)
			return (open_outfile(curs->next->str, 1));
		curs = curs->next;
	}
	if (curs && curs->type == PIPE)
	{
		return (pipefd[1]);
		// Envoyer le fd du pipefd[2], entree WRITE;
	}
	return (STDOUT_FILENO);
}

int redirect_input(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) == -1)
	{
		perror("Dup2 failed");
		return (1);
	}
	if (dup2(fdout, STDOUT_FILENO) == -1)
	{
		perror("Dup2 failed");
		return (2);
	}
	// Surement necessaire de fermer le pipe
	// Voire les fd dupliques genre : les commentaires
	return (0);
}