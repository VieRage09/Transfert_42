/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:36:41 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 15:48:38 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Checks for existence and readability of the infile in argument
// If it exists and is readable, opens it and returns the fd 
// Returns -1 on failure
int	open_infile(char *file_path)
{
	int	fd;

	if (!file_path)
		return (-1);
	if (!access(file_path, F_OK) && !access(file_path, R_OK))
	// File exists and we can read it 
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
// Return -1 on failure
int	open_outfile(char *file_path)
{
	int	fd;

	if (!file_path)
		return (-1);
	if (access(file_path, F_OK) == -1)
	// File doesn't exist
	{
		fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	}
	else
	// File does exist
	{
		if (access(file_path, W_OK) == -1)
		// Program doesn't have correct rights to write to this file
		{
			perror("Access failed");
			return (-1);
		}
		else
			fd = open(file_path, O_WRONLY);
	}
	if (fd == -1)
		perror("Open failed");
	return (fd);
}

// Takes a tab of fd created by pipe function
// Redirects fd_read and fd_write to the corresponding fd of the pipe tab
int	redirect(int *pipe_tab, int fd_read, int fd_write)
{
	if (!pipe_tab || fd_read == -1 || fd_write == -1)
		return (-1);
	if (dup2(fd_read, 0) == -1)
	{
		perror("Dup2 failed");
		return (-1);
	}
	if (dup2(fd_write, 1) == -1)
	{
		perror("Dup2 failed");
		return (-1);
	}
	close(pipe_tab[0]);
	close(pipe_tab[1]);
	return (0);
}

// Closes both end of the pipe tab in argument
void	free_close_pipe(int *pipe_tab)
{
	if (close(pipe_tab[0]) != 0 || close(pipe_tab[1]) != 0)
		perror("Close failed");
}
