/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:55 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/17 01:25:31 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_unset(char **cmd_tab, t_env **s_env, char ***env)
{
	int		i;
	t_env	*var;

	if (!cmd_tab || !*s_env)
		return (1);
	i = 1;
	while (cmd_tab[i])
	{
		var = find_variable(cmd_tab[i], *s_env);
		if (var != NULL)
		{
			if (var->prev)
				var->prev->next = var->next;
			if (var->next)
				var->next->prev = var->prev;
			// free_s_env_node(var);
		}
		i++;
	}
	update_env_tab(*s_env, env);
	return (0);
}
