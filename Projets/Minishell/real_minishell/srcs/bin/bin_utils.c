/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:02:56 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/25 21:59:49 by tlebon           ###   ########.fr       */
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

t_env	*find_variable(char *name, t_env *s_env)
{
	t_env	*curs;
	int		longest;

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
int already_exists(t_env *s_env, char *name)
{
	t_env *curs;
	int longest;

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

// Appends a new node to env_lst if there is no "name" named node inside it
// If there is a "name" named node, change its value (str) to value
// Push the modifications of env_lst to env_tab with update_env_tab function
int update_env(t_env **env_lst, char *name, char *value, char ***env_pt)
{
	t_env *var;

	if (already_exists(*env_lst, name) == 0)
		append_env_lst(env_lst, create_env(name, value)); // Attention a la gestion d'erreur ici
	else
	{
		var = find_variable(name, *env_lst);
		free(var->str);
		var->str = ft_strdup(value);
	}
	if (update_env_tab(*env_lst, env_pt, 1) != 0)
		return (1);
	return (0);
}