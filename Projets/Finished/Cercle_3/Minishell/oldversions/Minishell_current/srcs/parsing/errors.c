/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:24:50 by lberne            #+#    #+#             */
/*   Updated: 2024/11/06 15:51:54 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*if the prompt is empty it must NOT be added to history*/
bool	empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

/*no quote can be unclosed EXCEPT if in two quotes*/
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

/*main ft, check for open quotes or pipes at the end or beginning*/
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
