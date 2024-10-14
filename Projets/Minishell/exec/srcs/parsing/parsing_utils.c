/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:02:17 by lberne            #+#    #+#             */
/*   Updated: 2024/10/14 21:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_token(char *ingr, int step) //return le i correspondant au dernier char
{
	char	quote;
	
	//quote = 0;
	if (is_special(ingr[step]))
	{
		if (ingr[step] != '|' && ingr[step] == ingr[step + 1])
			step++;
	}
	else
	{
		while (!is_wspace(ingr[step]) && !is_special(ingr[step]))
		{
			if (is_quote(ingr[step]))// && quote == 0 && ingr[step + 1] != 0)
			{
				quote = ingr[step];
				//step++;
				while (ingr[step] != quote)
				{
					step++;
				}
				if (is_wspace(ingr[step + 1]) || is_special(ingr[step + 1]))
					return (step);
				//quote = 0;
				//continue ;
			}
			step++;
		}
	}
	printf("\nstep : %d | end of token : %c\n",step, ingr[step]);
	return (step);
}

int	chunk_len(char *ingredients, int step) //ignore $ for now
{
	int	len;

	if (is_special(ingredients[step]))
		return (3);
	while (!is_wspace(ingredients[step]) && !is_special(ingredients[step]))
	{
		len++;
		step++;
	}
	return (len);
}

bool	is_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return true;
	else
		return false;
}

bool	is_quote(char c)
{
	if (c == 34 || c == 39)
		return true;
	else
		return false;
}

bool	is_wspace(char c)
{
	if (c <= 32 || c == 127)
		return true;
	else
		return false;
}
