/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:41:55 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/25 21:52:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
void	free_env_node(t_env *s_env)
{
	if (!s_env)
		return ;
	if (s_env->prev)
		s_env->prev->next = s_env->next;
	if (s_env->next)
		s_env->next->prev = s_env->prev;
	if (!s_env->prev)
	{
		s_env->next->ret = s_env->ret;
	}
	free(s_env->name);
	free(s_env->str);
	free(s_env);
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
			free_env_node(var);
		i++;
	}
	update_env_tab(*s_env, env, 1);
	return (0);
}
