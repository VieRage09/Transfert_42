/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/13 09:18:48 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	exec_builtin(t_exec *s_exec)
{
	if (!s_exec)
		return (1);
	if (ft_strncmp(s_exec->cmd_tab[0], "echo", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_echo());
	else if (ft_strncmp(s_exec->cmd_tab[0], "cd", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_cd(s_exec->cmd_tab[1]));
	else if (ft_strncmp(s_exec->cmd_tab[0], "pwd", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_pwd());
	else if (ft_strncmp(s_exec->cmd_tab[0], "export", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_export(s_exec->cmd_tab, NULL));
	else if (ft_strncmp(s_exec->cmd_tab[0], "unset", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_unset());
	else if (ft_strncmp(s_exec->cmd_tab[0], "env", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_env(s_exec->env_tab));
	else if (ft_strncmp(s_exec->cmd_tab[0], "exit", ft_strlen(s_exec->cmd_tab[0])) == 0)
		return (exec_exit());
	return (0);
}

void continue_exec(t_token **s_token, int **pipefd, int *rdpipe)
{
	*s_token = search_next_pipe(*s_token);
	if (*s_token)
	{
		*s_token = (*s_token)->next;
		if (close((*pipefd)[1]) != 0)
			perror("Close (main process) failed");
		*rdpipe = (*pipefd)[0];
	}
}