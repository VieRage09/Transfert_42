/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:16:13 by lberne            #+#    #+#             */
/*   Updated: 2024/10/29 15:16:40 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
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

void	free_all(t_data	*data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->env_lst)
	{
		free_env_lst(data->env_lst);
		data->env_lst = NULL;
	}
}