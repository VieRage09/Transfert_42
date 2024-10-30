/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:44:49 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/16 23:55:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

// Checks the cmd
// If cmd is ok, executes it with execve, if the cmd isn' found,
// triggers error msg "cmd not found"
// Returns 127 on error cmd not found, 0 on success
int	execute(char *cmd, char **env)
{
	char	**cmd_tab;
	char	*path;

	path = NULL;
	if (!cmd || ft_str_is_wspace(cmd))
		cmd_tab = NULL;
	else
		cmd_tab = ft_split(cmd, ' ');
	if (cmd_tab)
		path = get_cmd_path(cmd_tab[0], env);
	if (!path)
	{
		path = cmd;
		write(2, "Command not found\n", 18);
	}
	if (execve(path, cmd_tab, env) == -1)
		perror("Execve failed");
	if (cmd_tab)
		ft_free_tab((void **)cmd_tab);
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (126);
	return (127);
}

// Instructions for the child process
// Opens the input file and redirects accordingly
// Then execute the cmd
static void	first_child(char *cmd, char **env, int *pipefd, char *infile)
{
	int	fdin;

	fdin = open_infile(infile);
	if (fdin == -1)
	{
		close_pipe(pipefd);
		exit(1);
	}
	if (redirect(pipefd, fdin, pipefd[1]) == -1)
		exit(4);
	if (close(fdin) != 0)
		perror("Close failed");
	exit(execute(cmd, env));
}

// Handles file opening errors (quits accordingly)
// Redirects input and output via first_child function
// Executes the correct command via first_child function
void	launch_first_process(char *cmd, char **env,
							char *infile, int *read_pipe)
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
		close_pipe(pipefd);
		perror("Fork failed");
		free(read_pipe);
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		free(read_pipe);
		first_child(cmd, env, pipefd, infile);
	}
	if (close(pipefd[1]) != 0)
		perror("Close failed");
	*read_pipe = pipefd[0];
}

// Instructions for the child process
// Opens the output file and redirects accordingly
static void	last_child(char *outfile, int *pipefd, int *read_pipe)
{
	int	fdout;

	fdout = open_outfile(outfile, 0);
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

// Handles file opening errors (quits accordingly)
// Redirects input and output via last_child function
// Executes the correct command via execute function
pid_t	launch_last_process(char *cmd, char **env,
							char *outfile, int *read_pipe)
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
		last_child(outfile, pipefd, read_pipe);
		exit(execute(cmd, env));
	}
	close_pipe(pipefd);
	if (close(*read_pipe) != 0)
		perror("Close failed");
	return (id);
}
