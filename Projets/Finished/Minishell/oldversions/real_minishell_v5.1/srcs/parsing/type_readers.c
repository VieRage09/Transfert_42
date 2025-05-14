/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_readers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:02:17 by lberne            #+#    #+#             */
/*   Updated: 2024/10/30 16:47:10 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_type(char	*chunk) //uniquement pipes et crocos, cmd et arg avec physio
{
	int	len;

	while (chunk)
	{
		len = ft_strlen(chunk);
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

void	physio(t_token *fruit_salad) //attribue le bon type en fonction de ceux deja trouves
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
