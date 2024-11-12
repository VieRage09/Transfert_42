/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:07:56 by lberne            #+#    #+#             */
/*   Updated: 2024/11/06 15:52:33 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*handle the exit keyword with the correct return code, see man*/
bool	ft_exit(t_token *tokens, t_data *data)
{
	t_token	*current;
	char	*str_ptr;

	if (tokens && tokens->str && match(tokens->str, "exit"))
	{
		current = tokens->next;
		if (current && current->next)
			return (printf("exit: too many arguments\n"), false);
		if (current && current->str)
		{
			str_ptr = current->str;
			while (*str_ptr)
			{
				if (!ft_isdigit(*str_ptr))
				{
					data->ret = 2;
					return (printf("exit: numeric argument required\n"), 1);
				}
				str_ptr++;
			}
			data->ret = ft_atoi(current->str) % 256;
		}
		return (true);
	}
	return (false);
}
