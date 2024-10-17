/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/17 01:32:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Is executed by child process of exec_cmd
// Search for path of the cmd via get_cmd_path
// Close fdin and fdout if they are != of STDIN or STDOUT
// Execute the cmd via execve
// AJOUTER DES TRUCS SI EXECVE FAIL
static void execute(t_exec *s_exec)
{
	char *path;

	if (!s_exec)
		return;
	path = get_cmd_path(s_exec->cmd_tab[0]);
	if (!path)
		path = s_exec->cmd_tab[0];
	if (s_exec->fdin != STDIN_FILENO)
	{
		if (close(s_exec->fdin) != 0)
			perror("Close failed");
	}
	if (s_exec->fdout != STDOUT_FILENO)
	{
		if (close(s_exec->fdout) != 0)
			perror("Close failed");
	}
	if (execve(path, s_exec->cmd_tab, s_exec->env_tab) != 0)
	{
		perror("Execve failed");
		return;
	}
}

// Creates a new process via fork
// Child process redirects STDIN and STDOUT to fdin and fdout then execute cmd
// Parent process only returns id of child process
// Returns -1 on error
int exec_cmd(t_exec *s_exec)
{
	int id;

	if (!s_exec)
		return (-1);

	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	if (id == 0)
	{
		if (redirect_input(s_exec->fdin, s_exec->fdout) != 0)
		{
			printf("Redirect input error :\n");
			return (-1);
		}
		execute(s_exec);
	}
	return (id);
}

// Is executed by child process of exec_builtin
// Closes fdin and fdout if != of STDIN or STDOUT
// Compare the cmd of cmd_tab (cmd_tab[0]) and launch the correct builtin
// Returns -1 on error or builtin values
static int execute_builtin(t_exec *s_exec, t_env **s_env, char ***env_pt)
{
	if (s_exec->fdin != STDIN_FILENO)
		if (close(s_exec->fdin) != 0)
			perror("Close failed");
	if (s_exec->fdout != STDOUT_FILENO)
		if (close(s_exec->fdout) != 0)
			perror("Close failed");
	if (!s_exec)
		return (-1);
	if (ft_strncmp(s_exec->cmd_tab[0], "echo", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_echo());
	else if (ft_strncmp(s_exec->cmd_tab[0], "cd", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_cd(s_exec->cmd_tab));
	else if (ft_strncmp(s_exec->cmd_tab[0], "pwd", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_pwd());
	else if (ft_strncmp(s_exec->cmd_tab[0], "export", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_export(s_exec->cmd_tab, s_env, env_pt));
	else if (ft_strncmp(s_exec->cmd_tab[0], "unset", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_unset(s_exec->cmd_tab, s_env, env_pt));
	else if (ft_strncmp(s_exec->cmd_tab[0], "env", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_env(*env_pt));
	else if (ft_strncmp(s_exec->cmd_tab[0], "exit", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_exit());
	return (-1);
}

// Creates a new process via fork
// Child process redirects STDIN and STDOUT to fdin and fdout
// then execute then exit execute_builtin
// Parent process only returns child id or -1 on error
int exec_builtin(t_exec *s_exec, t_env **s_env, char ***env_pt)
{
	int id;

	if (!s_exec || !*s_env || !*env_pt)
		return (-1);
	if (redirect_input(s_exec->fdin, s_exec->fdout) != 0)
	{
			printf("Redirect input error :\n");
			return (-1);
	}
	return (execute_builtin(s_exec, s_env, env_pt));
}

// Used to go to a new cycle of execution
// Searches for a pipe in s_token list
// If there is one, move the head of s_token list to the token after the pipe
// Closes writing end of the current pipe and update rd_pipe to the reading end
// of the current pipe
// If no pipe is found, s_token will be set to NULL and the exec loop will stop
void continue_exec(t_token **s_token, int *pipefd, int *rdpipe)
{
	*s_token = search_next_pipe(*s_token);
	
	if (*s_token)
	{
		*s_token = (*s_token)->next;
		*rdpipe = pipefd[0];
	}
	free(pipefd);
}