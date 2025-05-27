/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishes_normer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:32:22 by lberne            #+#    #+#             */
/*   Updated: 2024/11/25 16:37:46 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar_question_mark(char *new_str, t_data data)
{
	char	*ret;

	ret = ft_itoa(data.ret);
	if (!ret || !new_str)
		return ;
	ft_cat(new_str, ret, 0);
	free(ret);
}

/* self-explanatory */
int	get_endof_envname(char *str, int start)
{
	if (str[start] == '$')
		start++;
	else
	{
		while (ft_isalnum(str[start]))
			start++;
	}
	return (start);
}
