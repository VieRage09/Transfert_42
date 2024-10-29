/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:36:10 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/27 17:14:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns the first node of s_env that has a name equal to name
// Returns NULL on error or if no name names node is found
t_env	*find_variable(char *name, t_env *s_env)
{
	t_env	*curs;
	int		longest;

	if (!s_env || !name)
		return (NULL);
	curs = s_env;
	while (curs)
	{
		if (ft_strlen(name) > ft_strlen(curs->name))
			longest = ft_strlen(name);
		else
			longest = ft_strlen(curs->name);
		if (ft_strncmp(curs->name, name, longest) == 0)
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// Iterates through s_env and checks whether an env named name exists
// Returns 1 if it exits
// Returns 0 otherwise
int	already_exists(t_env *s_env, char *name)
{
	t_env	*curs;
	int		longest;

	curs = s_env;
	while (curs)
	{
		if (ft_strlen(curs->name) > ft_strlen(name))
			longest = ft_strlen(curs->name);
		else
			longest = ft_strlen(name);
		if (ft_strncmp(curs->name, name, longest) == 0)
			return (1);
		curs = curs->next;
	}
	return (0);
}

// Returns the value (s_env->str) of the first name named node encountered
// Returns NULL on error or if no name named node is found 
char	*get_env_str(t_env *s_env, char *name)
{
	t_env	*curs;

	if (!s_env || !name)
		return (NULL);
	curs = s_env;
	while (curs)
	{
		if (ft_strncmp(name, curs->name,
				ft_strlen(name) + ft_strlen(curs->name)) == 0)
			return (curs->str);
		curs = curs->next;
	}
	return (NULL);
}

// Updates the value (s_env->str) of the first name named node encountered
// If the value is != NULL, frees it before assigning str
// Returns 0 on succes, 1 on error
int	set_env_str(t_env **s_env, char *name, char *str)
{
	t_env	*curs;

	if (!s_env || !name || !str)
		return (1);
	curs = *s_env;
	while (curs)
	{
		if (ft_strncmp(name, curs->name,
				ft_strlen(name) + ft_strlen(curs->name)) == 0)
			break ;
		curs = curs->next;
	}
	if (curs->str)
		free(curs->str);
	curs->str = str;
	return (0);
}
