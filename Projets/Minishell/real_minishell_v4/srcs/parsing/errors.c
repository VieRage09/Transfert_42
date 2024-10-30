/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:24:50 by lberne            #+#    #+#             */
/*   Updated: 2024/10/30 16:31:22 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] >= 127)
		{
			perror("\033[0;101mnon ascii character\033[0m\n");
			free(line);
			return (true);
		}
		i++;
	}
	if (quote_error(line) || line[0] == '|' || line[ft_strlen(line + 1)] == '|') 
	{
		perror("\033[0;101mopen quote or pipe\033[0m\n");
		free(line);
		return (true);
	}
	return (false);
}
