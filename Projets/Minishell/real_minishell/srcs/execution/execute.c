/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/24 19:15:01 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Is executed by child process of exec_cmd
// Search for path of the cmd via get_cmd_path
// Close fdin and fdout if they are != of STDIN or STDOUT
// Execute the cmd via execve
// AJOUTER DES TRUCS SI EXECVE FAIL
static int execute(t_exec *s_exec, int fdin, int fdout, t_env *s_env)
{
	char *path;
	char **cmd_tab;

	if (!s_exec)
		return (1);
	cmd_tab = prepare_cmd_tab(s_exec->cmd_block);
	if (!cmd_tab)
		return (2);
	path = get_cmd_path(s_env, cmd_tab[0]);
	if (!path)
		path = cmd_tab[0];
	if (execve(path, cmd_tab, s_exec->env_tab) != 0)
	{
		perror("Execve failed");
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (126);
	return (127);
}

// Creates a new process via fork
// Child process redirects STDIN and STDOUT to fdin and fdout then execute cmd
// Parent process only returns id of child process
// Returns -1 on error
int exec_cmd(t_exec *s_exec, t_env *s_env)
{
	int id;
	int fdin;
	int fdout;

	fdin = -2;
	fdout = -2;
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
		if (set_fd_in_out(&fdin, &fdout, s_exec) != 0) // hd_tab est bien modifie mais dans l'enfant uniquement
			exit(1);
		printf("fdin = %i, fdout = %i\n", fdin, fdout);
		if (redirect_input(fdin, fdout) != 0)
		{
			ft_putstr_fd("Redirect input error :\n", 2);
			return (2);
		}
		exit(execute(s_exec, fdin, fdout, s_env));
	}
	return (id);
}

// Is executed by child process of exec_builtin
// Closes fdin and fdout if != of STDIN or STDOUT
// Compare the cmd of cmd_tab (cmd_tab[0]) and launch the correct builtin
// Returns > 0 on error or builtin values
static int execute_builtin(t_exec *s_exec, t_env **s_env, char ***env_pt)
{
	char **cmd_tab;

	cmd_tab = prepare_cmd_tab(s_exec->cmd_block);
	if (!cmd_tab)
		return (1);
	if (!s_exec)
		return (2);
	if (ft_strncmp(cmd_tab[0], "echo", ft_strlen(cmd_tab[0])) == 0)
		return (exec_echo(cmd_tab));
	else if (ft_strncmp(cmd_tab[0], "cd", ft_strlen(cmd_tab[0])) == 0)
		return (exec_cd(cmd_tab, s_env, env_pt));
	else if (ft_strncmp(cmd_tab[0], "pwd", ft_strlen(cmd_tab[0])) == 0)
		return (exec_pwd(*s_env));
	else if (ft_strncmp(cmd_tab[0], "export", ft_strlen(cmd_tab[0])) == 0)
		return (exec_export(cmd_tab, s_env, env_pt));
	else if (ft_strncmp(cmd_tab[0], "unset", ft_strlen(cmd_tab[0])) == 0)
		return (exec_unset(cmd_tab, s_env, env_pt));
	else if (ft_strncmp(cmd_tab[0], "env", ft_strlen(cmd_tab[0])) == 0)
		return (exec_env(*env_pt));
	else if (ft_strncmp(cmd_tab[0], "exit", ft_strlen(cmd_tab[0])) == 0)
		return (0);
	return (3);
}

static int	exec_builtin_pipeline(t_exec *s_exec, t_env **s_env, char ***env_pt)
{
	int	fdin;
	int	fdout;
	int	id;

	fdin = -2;
	fdout = -2;
	if (set_fd_in_out(&fdin, &fdout, s_exec) != 0)
		return (-1);
	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	if (id == 0)
	{
		if (redirect_input(fdin, fdout) != 0)
		{
			ft_putstr_fd("Redirect input error :\n", 2);
			return (1);
		}
		exit(execute_builtin(s_exec, s_env, env_pt));
	}
	return (id);
}
// Creates a new process via fork
// Child process redirects STDIN and STDOUT to fdin and fdout
// then execute then exit execute_builtin
// Parent process only returns child id or -1 on error
int exec_builtin(t_exec *s_exec, t_env **s_env, char ***env_pt)
{
	int ret;
	int fdin;
	int fdout;
	int	saved_stdin;
	int	saved_stdout;

	fdin = -2;
	fdout = -2;
	if (!s_exec || !*s_env || !*env_pt)
		return (1);
	if (search_next_pipe(s_exec->cmd_block) != NULL)
	{	
		printf("Builtin forked\n");
		return (exec_builtin_pipeline(s_exec, s_env, env_pt));
	}
	if (set_fd_in_out(&fdin, &fdout, s_exec) != 0)
		return (2);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (redirect_input(fdin, fdout) != 0)
	{
		ft_putstr_fd("Redirect input error :\n", 2);
		return (3);
	}
	ret = execute_builtin(s_exec, s_env, env_pt);
	if (redirect_input(saved_stdin, saved_stdout) != 0)
	{
		ft_putstr_fd("Redirection to STDIN STDOUT failed\n", 2);
		return (4);
	}
	return (ret);
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
	if (pipefd)
		if (close(pipefd[1]) != 0)
			perror("Close failed");
	if (*rdpipe > 0)
		if (close(*rdpipe) != 0)
			perror("Close failed");
	if (*s_token)
	{
		*s_token = (*s_token)->next;
		*rdpipe = pipefd[0];
	}
	free(pipefd);
}
