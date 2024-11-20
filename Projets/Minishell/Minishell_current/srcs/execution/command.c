/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:03:53 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/18 16:30:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_tab(int n_arg, t_token *cmd_token)
{
	char	**tab;
	t_token	*curs;

	tab = malloc((n_arg + 2) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(cmd_token->str);
	curs = cmd_token->next;
	n_arg = 1;
	while (curs && is_type(curs, ARG))
	{
		tab[n_arg] = ft_strdup(curs->str);
		n_arg++;
		curs = curs->next;
	}
	tab[n_arg] = NULL;
	return (tab);
}

// s_token MUST BE A CMD TOKEN
// Search for further ARG tokens after the CMD one then
// allocates tab accordingly
// Fills up tab with the cmd string and possible arg strings
// Ends the tab with (char *)0
char	**prepare_cmd_tab(t_token *s_token)
{
	t_token	*curs;
	t_token	*cmd_token;
	int		n_arg;

	if (!s_token)
		return (NULL);
	cmd_token = search_next_cmd(s_token);
	if (!cmd_token)
		return (NULL);
	curs = cmd_token;
	n_arg = 0;
	while (curs->next && is_type(curs->next, ARG))
	{
		n_arg++;
		curs = curs->next;
	}
	return (create_tab(n_arg, cmd_token));
}

// Creates a string of that form "cmdtab[i]/cmd"
// If the file corresponding to the path created exists and can be executed
// returns the path created
// Returns NULL otherwise
static char	*get_path(char *cmd, char **cmd_tab)
{
	int		i;
	char	*absolute_path;
	char	*prepared_cmd;

	if (!cmd || !cmd_tab)
		return (NULL);
	prepared_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (cmd_tab[i])
	{
		absolute_path = ft_strjoin(cmd_tab[i], prepared_cmd);
		if (access(absolute_path, F_OK) == 0)
			// && access(absolute_path, X_OK) == 0)
		{
			free(prepared_cmd);
			return (absolute_path);
		}
		i++;
		free(absolute_path);
	}
	free(prepared_cmd);
	return (NULL);
}

// Looks via get_path function through all the path of PATH varible to see
// if cmd corresponds to an existing and executable file 
// Returns its absolute path if yes
// Returns NULL if no
char	*get_cmd_path(t_env *s_env, char *cmd)
{
	char	*path;
	char	**path_tab;

	path = ft_strchr(cmd, '/');
	if (path)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);
		return (path);
	}
	path = get_env_str(s_env, "PATH");
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (NULL);
	path = get_path(cmd, path_tab);
	ft_free_tab((void **)path_tab);
	return (path);
}
