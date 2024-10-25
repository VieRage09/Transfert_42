/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:02:56 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/25 02:58:58 by tlebon           ###   ########.fr       */
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

int	update_env_tab(t_env *s_env, char ***env_pt, int do_free)
{
	t_env	*curs;
	int		size;

	if (!s_env)
		return (1);
	if (do_free)
		ft_free_tab((void **)*env_pt);
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
char	*get_env_str(t_env *s_env, char *name)
{
	t_env	*curs;

	if (!s_env || !name)
		return (NULL);
	curs = s_env;
	while (curs)
	{
		if (ft_strncmp(name, curs->name, ft_strlen(name) + ft_strlen(curs->name)) == 0)
			return (curs->str);
		curs = curs->next;
	}
	return (NULL);
}

int	set_env_str(t_env **s_env, char *name, char *str)
{
	t_env	*curs;

	if (!s_env || !name || !name)
		return (-1);
	curs = *s_env;
	while (curs)
	{
		if (ft_strncmp(name, curs->name, ft_strlen(name) + ft_strlen(curs->name)) == 0)
			break;
		curs = curs->next;
	}
	if (curs->str)
		free(curs->str);
	curs->str = str;
	return (0);
}
