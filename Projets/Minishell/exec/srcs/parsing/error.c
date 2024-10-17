/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:24:50 by lberne            #+#    #+#             */
/*   Updated: 2024/10/16 21:54:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_error(char *input)
{
	bool	open_quote;
	int		i;
	char	q;

	i = 0;
	open_quote = false;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (!open_quote)
			{
				q = input[i];
				open_quote = true;
			}
			else if (input[i] == q)
				open_quote = false;
		}
		i++;
	}
	return (open_quote);
}

bool	error_check(char *line)
{
	if (quote_error(line) || line[0] == '|' || line[ft_strlen(line + 1)] == '|') 
	{
		perror("\033[0;101mopen quote or pipe\033[0m\n");
		free(line);
		return (true);
	}
	return (false);
}
