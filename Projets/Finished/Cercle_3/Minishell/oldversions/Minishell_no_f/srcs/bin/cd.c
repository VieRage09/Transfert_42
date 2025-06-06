/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:37:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/11/12 23:26:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the path where we want to go with cd:
// HOME if ~ or nothing
// OLDPWD if -
// path is path
static char	*expand_path(t_env *s_env, char *path, int *print_pwd)
{
	char	*expanded_path;

	if (path == NULL || ft_strncmp(path, "~", ft_strlen(path)) == 0)
	{
		expanded_path = get_env_str(s_env, "HOME");
		printf("Path found by get_env_str = %s\n", expanded_path);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		expanded_path = get_env_str(s_env, "OLDPWD");
		*print_pwd = 1;
	}
	else
		expanded_path = path;
	return (expanded_path);
}

static int	cd_env_update(t_env **s_env, char *name, char *value, char ***env_pt)
{
	char	*tmp;
	
	tmp = ft_strjoin("=", value);	
	if (!tmp)
		return (2);
	update_env(s_env, name, tmp, env_pt);
	free(tmp);
	return (0);
}
// Check si il y a des subtilitees dans le comportement de cd dans bash
// Uses chdir to change the working directory to the path pointed to by path
// ttention SEGFAULT si OLDPWD est unset ???
// Attention SEGFAULT dans cas suivant : mkdir a --> cd a --> mkdir b --> cd b
// Si en etant dans b on supprime a : cd .. lance une erreur mais le 2eme appel a cd ..
// doit revenir effectivement en arriere soit au repertoire de base
int	exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt)
{
	char	*path;
	char	*old_pwd;
	int		print_pwd;

	print_pwd = 0;
	path = expand_path(*s_env, cmd_tab[1], &print_pwd);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	path = getcwd(NULL, 0);
	if (!path || !old_pwd)
		return (1);
	if (cd_env_update(s_env, "PWD", path, env_pt) != 0)
	{
		free(path);
		return (1);
	}
	free(path);
	if (cd_env_update(s_env, "OLDPWD", old_pwd, env_pt) != 0)
		return (1);
	if (print_pwd)
		exec_pwd(*s_env);
	free(old_pwd);
	return (0);
}
