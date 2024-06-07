/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:30:27 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/05 17:39:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../pipex_bonus.h"

// Checks for correct number of arguments, mallocs the double tab, 
// matching the requested number of pipes tabs 
// and uses pipe function on each entry 
// Returns a tab with the corresponding number of pipe tab
int	**menu(int ac) // malloc a proteger
{
	int	**tab;
	int	i;

	if (ac < 5)
	{
		ft_putstr_fd("This function takes 4 arguments or more\n", 2);
		exit(EXIT_FAILURE);
	}
	tab = malloc((ac - 4) * sizeof(int *));
	if (!tab)
		return (0);
	i = 0;
	while (i < ac - 4)
	{
		tab[i] = malloc(2 * sizeof(int));
		if (!tab[i])
			return (NULL);
		if (pipe(tab[i]) == -1)
		{
			perror("Pipe failed");
			return (NULL);
		}
		i++;
	}
	return (tab);
}

// Finds the HOME environnement variable in env pointer 
// Then trims it of HOME=
// Returns the path of the home 
// Returns NULL on failure or if HOME variable isn't found
static char	*get_home(char **env)
{
	int		i;
	char	*home;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")) == 0)
			break ;
		i++;
	}
	if (ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")) != 0)
		return (NULL);
	home = ft_substr(env[i], ft_strlen("HOME="), ft_strlen(env[i]));
	if (!home)
		return (NULL);
	return (home);
}

// Finds the PATH environnement variable in env pointer
// Then trims it of PATH=<home path>
// Returns the string containing only valid paths
// Returns NULL on failure or if PATH or HOME variables are not found
static char	*get_path(char **env)
{
	int		i;
	char	*path;
	char	*home;

	if (!env || env[0] == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	home = get_home(env);
	if (!home)
		return (NULL);
	path = ft_substr(env[i], ft_strlen("PATH=") + ft_strlen(home),
			ft_strlen(env[i]));
	free(home);
	if (!path)
		return (NULL);
	return (path);
}

static char	*cmd_path_check(char *cmd, char **path_tab)
{
	char	*cmd_link;
	int		i;
	char	*cmd_path;

	cmd_link = ft_strjoin("/", cmd);
	if (!cmd_link)
		return (NULL);
	i = 0;
	while (path_tab[i])
	{
		cmd_path = ft_strjoin(path_tab[i], cmd_link);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free(cmd_link);
	return (cmd_path);
}

// Splits the string returned by get_path function 
// Tries for each individual path if the file corresponding to cmd exists
// Returns the first valid path
// Returns NULL on failure or if no path is found
char	*get_cmd_path(char *cmd, char **env)
{
	char	**path_tab;
	char	*cmd_path;

	if (!cmd | !env)
		return (NULL);
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	cmd_path = get_path(env);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit (127);
	}
	path_tab = ft_split(cmd_path, ':');
	free(cmd_path);
	if (!path_tab)
		return (NULL);
	cmd_path = cmd_path_check(cmd, path_tab);
	ft_free_tab((void **) path_tab);
	return (cmd_path);
}
