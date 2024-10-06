/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:15:30 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/06 13:18:07 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *lst_str_chr(t_list *s_list, char *str)
{
	t_list *cursor;

	if (!s_list)
		return (NULL);
	cursor = s_list;
	while (cursor)
	{
		if (ft_strncmp((char *)cursor->content, str, ft_strlen(str)) == 0)
			return ((char *)cursor->content);
		cursor = cursor->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **cmd_tab)
{
	int	i;
	char	*absolute_path;
	char	*prepared_cmd;

	if (!cmd || !cmd_tab)
		return (NULL);
	prepared_cmd = ft_strjoin("/", cmd);	
	i = 0;
	while (cmd_tab[i])
	{
		absolute_path = ft_strjoin(cmd_tab[i], prepared_cmd);
		if (access(absolute_path, F_OK) == 0 && access(absolute_path, X_OK) == 0)
		{
			free(prepared_cmd);
			return (absolute_path);
		}
		i++;
	}
	return (NULL);
}

char *get_cmd_path(char *cmd)
{
	char	*path;
	char	**path_tab;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (NULL);
	return (get_path(cmd, path_tab));
}

int execute_lone_cmd(char *cmd, char **env)
{
	char	**cmd_tab;
	char	*path;
	int		id;

	if (!cmd || ft_str_is_wspace(cmd))
		cmd_tab = NULL;
	else
		cmd_tab = ft_split(cmd, ' ');
	if (cmd_tab)
		path = get_cmd_path(cmd_tab[0]);
	else
		path = NULL;
	if (path == NULL)
		path = cmd;
	printf("%s\n", path);
	id = fork();
	if (id == 0)
	{
		if (execve(path, cmd_tab, env) != 0)
			perror("Execve failed");
		return (127);
	}
	else
		wait(NULL);
	return (127);
}

// < Makefile cat | ls | echo > outfile

