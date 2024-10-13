/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:37:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/13 09:20:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check si il y a des subtilitees dans le comportement de cd dans bash
// Uses chdir to change the working directory to the path pointed to by path
// ttention SEGFAULT si OLDPWD est unset ???
// Attention SEGFAULT dans cas suivant : mkdir a --> cd a --> mkdir b --> cd b
// Si en etant dans b on supprime a : cd .. lance une erreur mais le 2eme appel a cd .. 
// doit revenir effectivement en arriere soit au repertoire de base
int exec_cd(char *path)
{
	char	*old_pwd;
	
	if (path == NULL)
	{
		if (chdir("/") != 0)
		{
			perror("cd"); // Pour un no such file or dir, bash ne renvoie pas exactement ca
			return (1);
		}
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		old_pwd = getenv("OLDPWD");
		if (!old_pwd)
			return (1);	// Error msg ?? Return value ??
		if (chdir(old_pwd) != 0)
		{
			perror("cd");
			return (1);
		}
		exec_pwd();
	}
	else
	{
		if (chdir(path) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	exec_pwd();
	return (0);
}
