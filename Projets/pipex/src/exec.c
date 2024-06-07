/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:44:49 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/05 17:33:59 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Checks the cmd
// If cmd is ok, executes it with execve, if the cmd isn' found,
// triggers error msg "cmd not found"
// Returns 127 on error cmd not found, 0 on success
int	execute(char *cmd, char **env) // split a proteger
{
	char	**cmd_tab;
	char	*path;

	if (!cmd || ft_str_is_wspace(cmd))
	{
		cmd_tab = NULL;
		path = NULL;
	}
	else
	{
		cmd_tab = ft_split(cmd, ' ');
		path = get_cmd_path(cmd_tab[0], env);
	}
	if (!path || !cmd_tab)
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

// Handles file opening errors (quits accordingly)
// Redirects input and output via redirect function
// Executes the correct command via execute function
pid_t	launch_first_process(char *cmd, char *infile, int *pipe_tab, char **env)
{
	int	fdin;
	int	id;

	id = fork(); //	Creation of first process
	if (id == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		fdin = open_infile(infile);
		if (fdin == -1)
		{
			free_close_pipe(pipe_tab);
			exit(1);
		}
		if (redirect(pipe_tab, fdin, pipe_tab[1]) == -1)
			exit(4);
		if (close(fdin) != 0)
			perror("Close failed");
		exit(execute(cmd, env));
	}
	return (id);
}

// Handles file opening errors (quits accordingly)
// Redirects input and output via redirect function
// Executes the correct command via execute function
pid_t	launch_last_process(char *cmd, char *outfile, int *pipe_tab, char **env)
{
	int	fdout;
	int	id;

	id = fork(); //	Creation of second process
	if (id == -1)
	{
		perror("Fork failed");
		return (EXIT_FAILURE);
	}
	if (id == 0)
	{
		fdout = open_outfile(outfile);
		if (fdout == -1)
		{
			free_close_pipe(pipe_tab);
			exit(1);
		}
		if (redirect(pipe_tab, pipe_tab[0], fdout) == -1)
			exit(4);
		if (close(fdout) != 0)
			perror("Close failed");
		exit(execute(cmd, env));
	}
	return (id);
}

// Waits for both childs to finish properly then returns the correct status_code
int	get_status_code(int last_cmd_id)
{
	int	wstatus1;
	int	wstatus2;
	int	wid;
	int	statuscode;

	wid = 0;
	statuscode = 0;
	wait(&wstatus1);
	wid = wait(&wstatus2);
	if (wid == last_cmd_id)
	{
		if (WIFEXITED(wstatus2))
			statuscode = WEXITSTATUS(wstatus2);
	}
	else
	{
		if (WIFEXITED(wstatus1))
			statuscode = WEXITSTATUS(wstatus1);
	}
	return (statuscode);
}
