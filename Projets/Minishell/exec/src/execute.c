/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:22:46 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/10 16:33:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void execute_cmd(int fdin, char **cmd_tab, int fdout, char **env)
{
	char *path;
	int ret;

	ret = redirect_input(fdin, fdout);
	if (ret != 0)
	{
		printf("Redirect input error : %i\n", ret);
		return;
	}
	path = get_cmd_path(cmd_tab[0]);
	if (!path)
		path = cmd_tab[0];
	if (fdin != STDIN_FILENO)
	{
		if (close(fdin) != 0)
			perror("Close failed");
	}
	if (fdout != STDOUT_FILENO)
	{
		if (close(fdout) != 0)
			perror("Close failed");
	}
	if (execve(path, cmd_tab, env) != 0)
	{
		perror("Execve failed");
		return;
	}
}