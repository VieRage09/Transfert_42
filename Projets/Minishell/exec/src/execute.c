/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/11 21:06:30 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_cmd(t_exec *s_exec)
{
	char *path;
	int ret;

	if (!s_exec)
		return ;
	ret = redirect_input(s_exec->fdin, s_exec->fdout);
	if (ret != 0)
	{
		printf("Redirect input error : %i\n", ret);
		return;
	}
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