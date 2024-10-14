/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:03:53 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/14 18:59:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterates s_token from start (s_token) to a pipe token or end of list
// Returns a pointer to the first cmd token found
t_token *search_next_cmd(t_token *s_token)
{
	t_token *curs;

	curs = s_token;
	while (curs && curs->type != PIPE)
	{
		if (curs->type == CMD)
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// s_token MUST BE A CMD TOKEN
// Search for further ARG tokens after the CMD one then
// allocates tab accordingly
// Fills up tab with the cmd string and possible arg strings
// Ends the tab with (char *)0
char **prepare_cmd_tab(t_token *s_token)
{
	t_token *curs;
	t_token	*cmd_token;
	char **tab;
	int n_arg;

	if (!s_token)
		return (NULL);
	cmd_token = search_next_cmd(s_token);
	if (!cmd_token)
		return (NULL);
	curs = cmd_token;
	n_arg = 0;
	while (curs->next && curs->next->type == ARG)
	{
		n_arg++;
		curs = curs->next;
	}
	tab = malloc((n_arg + 2) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = cmd_token->str;
	curs = cmd_token->next;
	n_arg = 1;
	while (curs && curs->type == ARG)
	{
		tab[n_arg] = curs->str;
		n_arg++;
		curs = curs->next;
	}
	return (tab);
}

static char	*get_path(char *cmd, char **cmd_tab)
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