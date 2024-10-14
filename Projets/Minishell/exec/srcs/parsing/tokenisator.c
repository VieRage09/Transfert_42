/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:39:07 by lberne            #+#    #+#             */
/*   Updated: 2024/10/14 21:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_type(char	*chunk)
{
	int	len;

	while (chunk)
	{
		len = strlen(chunk);
		if (!ft_strncmp(chunk, "|", len))
			return(PIPE);
		else if (!ft_strncmp(chunk, "<", len))
			return(R_IN);
		else if (!ft_strncmp(chunk, "<<", len))
			return(HEREDOC);
		else if (!ft_strncmp(chunk, ">", len))
			return(R_OUT);
		else if (!ft_strncmp(chunk, ">>", len))
			return(R_OUT_APPEND);
		else
			return(-1);
	}
	return (-1);
}

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
	t_token	*new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("Failed memory allocation in create_token (tokenisator.c)");
		return (NULL);
	}
	new_token->str = ft_strdup(str);
	new_token->type = type;
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
