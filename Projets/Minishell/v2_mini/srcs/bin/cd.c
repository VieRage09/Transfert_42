/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:37:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/27 17:15:59 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the path where we want to go with cd:
// HOME if ~ or nothing
// OLDPWD if -
// path is path
char	*expand_path(t_env *s_env, char *path, int *print_pwd)
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
		return (errno);
	}
	path = getcwd(NULL, 0);
	update_env(s_env, "PWD", path, env_pt);
	update_env(s_env, "OLDPWD", old_pwd, env_pt);
	if (print_pwd)
		exec_pwd(*s_env);
	free(path);
	free(old_pwd);
	return (0);
}
