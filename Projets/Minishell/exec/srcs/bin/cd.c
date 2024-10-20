/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:37:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/21 00:40:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check si il y a des subtilitees dans le comportement de cd dans bash
// Uses chdir to change the working directory to the path pointed to by path
// ttention SEGFAULT si OLDPWD est unset ???
// Attention SEGFAULT dans cas suivant : mkdir a --> cd a --> mkdir b --> cd b
// Si en etant dans b on supprime a : cd .. lance une erreur mais le 2eme appel a cd .. 
// doit revenir effectivement en arriere soit au repertoire de base
int exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt)
{
	char	*path;
	char	*old_pwd;
	int		print_pwd;

	print_pwd = 0;
	path = cmd_tab[1];	
	if (path == NULL)
	{
		// path = get_env_str(*s_env, "HOME");
		path = getenv("HOME");
		printf("Path found by get_env_str = %s\n", path);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		path = get_env_str(*s_env, "OLDPWD");
		// path = getenv("OLDPWD");
		if (!path)
			return (1);	// Error msg ?? Return value ??
		print_pwd = 1;
	}
	old_pwd = getenv("PWD");
	if (!old_pwd)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	path = getcwd(NULL, 0);
	update_env(s_env, "PWD", path,  env_pt);
	update_env(s_env, "OLDPWD", old_pwd,  env_pt);
	if (print_pwd)
		exec_pwd(*s_env);
	free(path);
	return (0);
}

// Si cd -e --> retour a HOME