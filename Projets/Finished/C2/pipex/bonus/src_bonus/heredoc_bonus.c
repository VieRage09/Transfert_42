/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 19:57:35 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/16 23:46:01 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

// Gets the input of heredoc via get_next_line function
// Then redirects accordingly and execute the cmd
static void	manage_heredoc(char *cmd, char **env, char *eof, int *pipefd)
{
	char	*input;
	int		temp_pipe[2];

	if (pipe(temp_pipe) != 0)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	input = get_next_line(0);
	while (input)
	{
		if (ft_strlen(input) == ft_strlen(eof) + 1
			&& ft_strncmp(eof, input, ft_strlen(eof)) == 0)
		{
			if (redirect(pipefd, temp_pipe[0], pipefd[1]) == -1)
				exit(4);
			close_pipe(temp_pipe);
			free(input);
			exit(execute(cmd, env));
		}
		write(temp_pipe[1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
	}
}

// Creates a pipe and a child process to launch the first command
// Handles the heredoc input, redirection and launch via manage_heredoc function
static void	first_hd_process(char *cmd, char *eof, int *read_pipe,
								char **env)
{
	int	id;
	int	pipefd[2];

	if (pipe(pipefd) != 0)
	{
		perror("Pipe failed");
		free(read_pipe);
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		free(read_pipe);
		exit(EXIT_FAILURE);
	}
	if (id == 0)
		manage_heredoc(cmd, env, eof, pipefd);
	else
	{
		if (close(pipefd[1]) != 0)
			perror("Close failed");
		*read_pipe = pipefd[0];
	}
}

// Instructions for child process
// Opens the outfile and redirects accordingly
static void	last_child_hd(char *outfile, int *pipefd, int *read_pipe)
{
	int	fdout;

	fdout = open_outfile(outfile, 1);
	if (fdout == -1)
	{
		close_pipe(pipefd);
		if (close(*read_pipe) != 0)
			perror("Close failed");
		free(read_pipe);
		exit(1);
	}
	if (redirect(pipefd, *read_pipe, fdout) == -1)
	{
		free(read_pipe);
		exit(4);
	}
	if (close(fdout) != 0 || close(*read_pipe) != 0)
		perror("Close failed");
	free(read_pipe);
}

// Manages the last cmd if heredoc 
// (same as launch_last_cmd but outfile is open with append option)
static pid_t	last_hd_process(char *cmd, char *outfile, int *read_pipe,
									char **env)
{
	int	id;
	int	pipefd[2];

	if (pipe(pipefd) != 0)
	{
		perror("Pipe failed");
		return (EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		return (EXIT_FAILURE);
	}
	if (id == 0)
	{
		last_child_hd(outfile, pipefd, read_pipe);
		exit(execute(cmd, env));
	}
	close_pipe(pipefd);
	if (close(*read_pipe) != 0)
		perror("Close failed");
	return (id);
}

// Manages the unfolding of the heredoc program
// Returns the status code of the last cmd
int	hd_pipex(int ac, char **av, char **envp)
{
	int		*read_pipe;
	pid_t	id2;
	char	**mid_cmd_tab;

	read_pipe = malloc(sizeof(int));
	if (!read_pipe)
		exit(EXIT_FAILURE);
	*read_pipe = 0;
	first_hd_process(av[3], av[2], read_pipe, envp);
	if (ac - 5 > 1)
	{
		mid_cmd_tab = get_middle_cmd_tab(ac, av);
		middle_cmd_loop(mid_cmd_tab, read_pipe, envp);
		ft_free_tab((void **)mid_cmd_tab);
	}
	id2 = last_hd_process(av[ac - 2], av[ac - 1], read_pipe, envp);
	free(read_pipe);
	return (get_status_code(id2, ac - 4));
}
