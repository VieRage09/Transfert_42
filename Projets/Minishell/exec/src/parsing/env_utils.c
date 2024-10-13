/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:55:37 by lberne            #+#    #+#             */
/*   Updated: 2024/10/13 19:20:26 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env   *create_env(char *name, char *str)
{
    t_env   *new_env = (t_env *)malloc(sizeof(t_env));
    if (!new_env)
    {
        perror("Failed memory allocation in create_env");
        return NULL;
    }
    new_env->name = ft_strdup(name);
	new_env->str = ft_strdup(str);
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
    while (v_env[i] && i <= 5) //ici on s'arret a 5 POUR LES TESTS
    {
		//printf("hello create env lst %d\n", i);
		temp_env = ft_split(v_env[i], '=');
		name = ft_strdup(temp_env[0]);
		str = ft_strdup(temp_env[1]);
		//printf("hello name %s and str %s\n", name, str);
        append_env_lst(&env_lst, create_env(name, str));
        i++;
    }
    
    return (env_lst);
}

void    free_env_lst(t_env  *head)
{
    t_env   *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
		free(tmp->name);
        free(tmp->str);
        free(tmp);
    }
}
