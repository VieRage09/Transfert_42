/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:55:37 by lberne            #+#    #+#             */
/*   Updated: 2024/10/30 21:56:00 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_extractor(char *name, t_env *env_lst)
{
	t_env	*current;
	
	current = env_lst;
	while (current)
	{
		if (match(name, current->name))
			return (current->str);
		current = current->next;
	}
	return (NULL);
}

char	*get_env(char *token, int start, t_env *env_lst)
{
	char	*name;
	char	*res;
	int		i;
	
	if (!token)
		return (NULL);
	name = (char *)malloc(sizeof(char) * ft_strlen(token) + 18);
	if (!name)
		return (NULL);
	name[0] = '\0';
	i = 0;
	if	(token[start] == '$')
		ft_cat(name, "SYSTEMD_EXEC_PID", 0);
	else
	{
		while (!is_wspace(token[start]) && !is_quote(token[start]) && token[start] != '$')
		{
			name[i++] = token[start++];
			name[i] = '\0';
		}
	}
	res = env_extractor(name, env_lst);
	free(name);
	return (res);
}

t_env   *create_env(char *name, char *str, bool printed)
{
    t_env   *new_env = (t_env *)malloc(sizeof(t_env));
    if (!new_env)
    {
        perror("Failed memory allocation in create_env");
        return NULL;
    }
    new_env->name = ft_strdup(name);
	new_env->str = ft_strdup(str);
	new_env->printed = printed;
	new_env->ret = 0;
    new_env->prev = NULL;
    new_env->next = NULL;
    return (new_env);
}

void    append_env_lst(t_env **head, t_env *new_env)
{
    t_env   *last;

    if (!*head)
        *head = new_env;
    else
    {
        last = *head;
        while (last->next != NULL)
            last = last->next;
        last->next = new_env;
        new_env->prev = last;
    }
}

t_env   *create_env_lst(char **v_env)
{
    t_env   *env_lst;
	char	**temp_env;
	char	*name;
	char	*str;
    int i;

	env_lst = NULL;
    i = 0;
    while (v_env[i])
    {
		if (!(temp_env = ft_split(v_env[i], '=')))
			return (NULL);
		name = ft_strdup(temp_env[0]);
		str = ft_strdup(temp_env[1]);
		if (!name || !str)
			return (NULL);
        append_env_lst(&env_lst, create_env(name, str, true));
    	ft_free_tab((void**)temp_env);
		free(name);
		free(str);
        i++;
    }
    return (env_lst);
}
