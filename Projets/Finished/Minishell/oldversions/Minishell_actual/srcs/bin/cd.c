/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:37:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/25 21:38:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the path where we want to go with cd:
// HOME if ~ or nothing
// OLDPWD if -
// path is path
// Returns NULL if environment variables HOME and OLDPWD are needed but unset
static char	*expand_path(t_env *s_env, char *path, int *print_pwd)
{
	char	*expanded_path;

	if (path == NULL || ft_strncmp(path, "~", ft_strlen(path)) == 0)
	{
		expanded_path = get_env_str(s_env, "HOME");
		if (!expanded_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		expanded_path = get_env_str(s_env, "OLDPWD");
		if (!expanded_path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		*print_pwd = 1;
	}
	else
		expanded_path = path;
	return (expanded_path);
}

// Checks if name is an existing environment variable
// If it is, updates it with its new value
// Returns 0 if the variable doesn't exists or on success
// Returns 1 on error
static int	cd_env_update(t_env **s_env, char *name, char *value,
							char ***env_pt)
{
	char	*tmp;

	if (!env_extractor(name, *s_env))
		return (0);
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (1);
	update_env(s_env, name, tmp, env_pt);
	free(tmp);
	return (0);
}

static int	change_directory(char **bfcd_cwd, char **path)
{
	if (!path)
		return (1);
	*bfcd_cwd = getcwd(NULL, 0);
	if (!*bfcd_cwd)
		*bfcd_cwd = ft_strdup("");
	if (chdir(*path) != 0)
	{
		free(*bfcd_cwd);
		ft_putstr_fd("minishell: cd: ", 2);
		perror(*path);
		return (1);
	}
	*path = getcwd(NULL, 0);
	if (!*path)
	{
		free(*bfcd_cwd);
		perror("minishell: cd: error retrieving current directory: getcwd");
		return (1);
	}
	return (0);
}

int	exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt)
{
	char	*path;
	char	*bfcd_cwd;
	int		print_pwd;

	print_pwd = 0;
	path = expand_path(*s_env, cmd_tab[1], &print_pwd);
	if (change_directory(&bfcd_cwd, &path) != 0)
		return (1);
	if (cd_env_update(s_env, "PWD", path, env_pt) != 0)
	{
		free(bfcd_cwd);
		free(path);
		return (3);
	}
	free(path);
	if (cd_env_update(s_env, "OLDPWD", bfcd_cwd, env_pt) != 0)
	{
		free(bfcd_cwd);
		return (4);
	}
	free(bfcd_cwd);
	if (print_pwd)
		exec_pwd(*s_env);
	return (0);
}
