/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:02:56 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/17 18:29:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_full_string(t_env *s_env)
{
	char	*name_prep;
	char	*result;


	if (!s_env)
		return (NULL);
	name_prep = ft_strjoin(s_env->name, "=");
	if (!name_prep)
		return (NULL);
	result = ft_strjoin(name_prep, s_env->str);
	if (!result)
	{
		free(name_prep);
		return (NULL);
	}
	free(name_prep);
	return (result);
}

int	update_env_tab(t_env *s_env, char ***env_pt)
{
	t_env	*curs;
	int		size;

	if (!s_env)
		return (1);
	// if (*env_pt)				// Donne un bus error sur les macs de l'ecole, mais surement necessaire pour eviter leaks
		// free(*env_pt);
	curs = s_env;
	size = 0;
	while (curs)
	{
		size++;
		curs = curs->next;
	}
	*env_pt = malloc((size + 1) * sizeof(char *));
	if (!(*env_pt))
		return (-1);
	curs = s_env;
	size = 0;
	while (curs)
	{
		(*env_pt)[size++] = create_full_string(curs); 
		curs = curs->next;
	}
	(*env_pt)[size] = NULL;
	return (0);
}
	