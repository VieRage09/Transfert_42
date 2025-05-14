/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:39:07 by lberne            #+#    #+#             */
/*   Updated: 2024/10/24 00:24:23 by tlebon           ###   ########.fr       */
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

t_token	*create_token(const char *str, int type)
{
	int	i;

	i = 0;
	t_token	*new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("Failed memory allocation in create_token (tokenisator.c)");
		return (NULL);
	}
	new_token->str = ft_strdup(str);
	new_token->type = type;
	new_token->hello_there = false;
	while (str[i])
	{
		if (is_quote(str[i]) || str[i] == '$')
			new_token->hello_there = true;
		i++;
	}
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!*head)
		*head = new_token; //pas encore de token, le nouveau devient head
	else
	{
		last = *head;
		while (last->next != NULL) //reach the last token
			last = last->next;
		last->next = new_token; //new token est place apres le last
		new_token->prev = last; //l'ancien last est lie au new token (qui est devenu le last)
	}
}
