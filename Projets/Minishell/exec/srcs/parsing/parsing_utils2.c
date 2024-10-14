/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:19 by lberne            #+#    #+#             */
/*   Updated: 2024/10/14 21:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//vire les quotes, remplace les $ dans " " et donne les types
void	physio(t_token *fruit_salad)
{
	t_token	*current;
	bool	next_is_cmd;

	current = fruit_salad;
	next_is_cmd = true;
	while (current != NULL)
	{
		if (current->type < 0)
		{
			if (current->prev == NULL)
			{
				current->type = CMD;
				next_is_cmd = false;
			}
			else if (current->prev->type >= 1 && current->prev->type <= 4)
				current->type = ARG;
			else if (next_is_cmd)
			{
				current->type = CMD;
				next_is_cmd = false;
			}
			else
				current->type = ARG;
		}
		else if (current->type == PIPE)
			next_is_cmd = true;
		current = current->next;
	}
}

void	clear_str(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
}

size_t	subtil(char	*str) //ajouter longueur des $ENV
{
	size_t	res;
	int		i;
	
	res = 0;
	i = 0;
	while (str[i])
	{
		i++;
		res++;
	}
	return (res);
}