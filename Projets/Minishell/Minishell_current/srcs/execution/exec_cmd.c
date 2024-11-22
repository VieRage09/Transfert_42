/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/22 17:54:25 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Is executed by child process of exec_cmd
// Search for path of the cmd via get_cmd_path
// Close fdin and fdout if they are != of STDIN or STDOUT
// Execute the cmd via execve
// AJOUTER DES TRUCS SI EXECVE FAIL
static int	execute(t_exec *s_exec, t_env *s_env)
{
	char	*path;
	char	**cmd_tab;

	if (!s_exec)
		return (1);
	cmd_tab = prepare_cmd_tab(s_exec->cmd_block);
	if (!cmd_tab)
		return (2);
	path = get_cmd_path(s_env, cmd_tab[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab((void **)cmd_tab);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		ft_free_tab((void **)cmd_tab);
		free(path);
		return (126);
	}
	if (execve(path, cmd_tab, s_exec->env_tab) != 0)
		perror("Execve failed");
	ft_free_tab((void **)cmd_tab);
	free(path);
	return (127);
}

// Creates a new process via fork
// Child process redirects STDIN and STDOUT to fdin and fdout then execute cmd
// Parent process only returns id of child process
// Returns -1 on error
int	exec_cmd(t_manager *s_manager, t_env *s_env, char ***env_pt)
{
	int	id;
	int	fdin;
	int	fdout;

	fdin = -2;
	fdout = -2;
	if (!s_manager || !s_env || !*env_pt) // RAJOUTE *env_pt pour la secu
		return (-1);
	id = fork();
	if (id == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	if (id == 0)
	{
		if (set_fd_in_out(&fdin, &fdout, s_manager) != 0)
			exit(1);
		printf("fdin = %i, fdout = %i\n", fdin, fdout);
		if (redirect_input(fdin, fdout) != 0)
		{
			ft_putstr_fd("Redirect input error :\n", 2);
			exit (2);
		}
		exit(execute(s_manager->s_exec, s_env));
	}
	return (id);
}

// Used to go to a new cycle of execution
// Searches for a pipe in s_token list
// If there is one, move the head of s_token list to the token after the pipe
// Closes writing end of the current pipe and update rd_pipe to the reading end
// of the current pipe
// If no pipe is found, s_token will be set to NULL and the exec loop will stop
void	continue_exec(t_token **s_token, t_manager *s_manager)
{
	if (s_manager->prev_pipe)
	{
		if (close(s_manager->prev_pipe[0]) != 0)
			perror("Close failed(Continue exec prev_pipe[0])");
		free(s_manager->prev_pipe);
	}
	if (s_manager->pipefd)
	{
		s_manager->prev_pipe = s_manager->pipefd;
		if (close(s_manager->pipefd[1]) != 0)
			perror("Close failed");
		s_manager->pipefd = NULL;
	}
	*s_token = search_next_token(*s_token, PIPE);
	if (*s_token)
		*s_token = (*s_token)->next;
}
