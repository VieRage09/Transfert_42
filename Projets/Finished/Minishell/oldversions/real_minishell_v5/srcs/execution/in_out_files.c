/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:14:16 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/04 18:11:14 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks for existence and readability of the infile in argument
// If it exists and is readable, opens it and returns the fd
// Returns -1 on failure
int open_infile(char *file_path)
{
	int fd;

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
int open_outfile(char *file_path, int append)
{
	int fd;

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
			printf("append 1\n");
		}
		else
			fd = open(file_path, O_WRONLY | O_TRUNC);
	}
	if (fd == -1)
		perror("Open failed");
	return (fd);
}

static int assign_input(int *fdin, t_token *s_token, int **hd_tab)
{
	if (!s_token)
		return (1);
	if (is_type(s_token, R_IN) && s_token->next && is_type(s_token->next, ARG))
	{
		if (*fdin > 2)
			if (close(*fdin) != 0)
				perror("Close failed");
		*fdin = open_infile(s_token->next->str);
	}
	else if (is_type(s_token, HEREDOC) && s_token->next && is_type(s_token->next, ARG))
	{
		if (*fdin > 2)
			if (close(*fdin) != 0)
				perror("Close failed");
		*fdin = chose_hd_fd(hd_tab);
	}
	return (0);
}

static int assign_output(int *fdout, t_token *s_token)
{
	if (!s_token)
		return (1);
	if (is_type(s_token, R_OUT) && s_token->next && is_type(s_token->next, ARG))
	{
		if (*fdout > 2)
			if (close(*fdout) != 0)
				perror("Close failed");
		*fdout = open_outfile(s_token->next->str, 0);
	}
	else if (is_type(s_token, R_OUT_APPEND) && s_token->next && is_type(s_token->next, ARG))
	{
		if (*fdout > 2)
			if (close(*fdout) != 0)
				perror("Close failed");
		*fdout = open_outfile(s_token->next->str, 1);
	}
	return (0);
}

static void	assign_pipe(int *fdin, int *fdout, t_manager *s_manager, t_token *s_token)
{
	if (*fdin == -2) // donc aucun operateur de redirection n'a ete trouve ou il y en a un mais il est seul cette grosse merde
	{
		if (s_manager->s_exec->cmd_block->prev && is_type(s_manager->s_exec->cmd_block->prev, PIPE))
		{
			printf("rdpipe returned as fdin\n");
			*fdin = s_manager->s_exec->readpipe;
		}
		else
			*fdin = STDIN_FILENO;
	}
	if (*fdout == -2)
	{
		if (s_token && is_type(s_token, PIPE))
			*fdout = s_manager->s_exec->pipefd[1];
		else
			*fdout = STDOUT_FILENO;
	}
}
// Iterates on the prompt until its end or a token PIPE
// For each redirection operators encountered, opens the corresponding
// file and assigns its fd to fdin/out after closing their precedent fd (if it exists)
// If no redirection operator is encountered but there is a PIPE token before or after
// cmd block, assign the correct READ/WRITE entry of pipefd to fdin/fdout
// Otherwise, assigns STDIN/OUT to fdin/out
int set_fd_in_out(int *fdin, int *fdout, t_manager *s_manager)
{
	t_token *curs;

	if (!s_manager)
		return (1);
	curs = s_manager->s_exec->cmd_block;
	while (curs && !is_type(curs, PIPE))
	{
		if (assign_input(fdin, curs, s_manager->hd_tab) != 0)
			return (2);
		if (assign_output(fdout, curs) != 0)
			return (3);
		curs = curs->next;
	}
	if (*fdin == -1 || *fdout == -1)
		return (4);
	assign_pipe(fdin, fdout, s_manager, curs);
	printf("fdin = %i fdout = %i\n", *fdin, *fdout);
	return (0);
}

// Redirect STDIN and STDOUT to fdin and fdout
// Close fdin and fdout after redirection
// If stin/out is STDIN/OUT the redirection does nothing more but fdin(STDIN) for ex is not closed
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
	if (fdin != STDIN_FILENO)
		if (close(fdin) != 0)
			perror("Close failed");
	if (fdout != STDOUT_FILENO)
		if (close(fdout) != 0)
			perror("Close failed");
	// Surement necessaire de fermer le pipe
	// Voire les fd dupliques genre : les commentaires
	return (0);
}
