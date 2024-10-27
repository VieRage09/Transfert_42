/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:15:30 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/27 17:50:35 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A RETIRER
// Debug function
void	print_cmd(t_token *s_token)
{
	t_token	*curs;

	curs = s_token;
	while (curs)
	{
		ft_print_str(curs->str);
		ft_print_str(" ");
		curs = curs->next;
	}
	ft_print_str("\n");
}

// Iterates s_token from start (s_token) to a pipe token or end of list
// Returns a pointer to the first cmd token found
t_token	*search_next_cmd(t_token *s_token)
{
	t_token	*curs;

	curs = s_token;
	while (curs && !is_type(curs, PIPE))
	{
		if (is_type(curs, CMD))
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}

// Iterates through s_token until it finds a token of type type
// If it founds one, return a pointer to that token
// If the iteration went until the end of the list returns NULL
t_token	*search_next_token(t_token *s_token, int type)
{
	t_token	*curs;

	if (!s_token)
		return (NULL);
	curs = s_token;
	while (curs)
	{
		if (is_type(curs, type))
			return (curs);
		curs = curs->next;
	}
	return (NULL);
}
