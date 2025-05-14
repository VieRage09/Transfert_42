/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_pipe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:36:41 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/16 20:42:36 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

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

// Takes a tab of fd created by pipe function
// Redirects fd_read and fd_write to the corresponding fd of the pipe tab
int	redirect(int *pipefd, int fd_read, int fd_write)
{
	if (fd_read == -1 || fd_write == -1)
	{
		close_pipe(pipefd);
		return (-1);
	}
	if (dup2(fd_read, 0) == -1)
	{
		perror("Dup2 failed");
		close_pipe(pipefd);
		return (-1);
	}
	if (dup2(fd_write, 1) == -1)
	{
		perror("Dup2 failed");
		close_pipe(pipefd);
		return (-1);
	}
	close_pipe(pipefd);
	return (0);
}

// Closes both end of the pipe tab in argument
void	close_pipe(int *pipe)
{
	if (close(pipe[0]) != 0 || close(pipe[1]) != 0)
		perror("Close failed");
}
