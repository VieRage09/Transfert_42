/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:11:12 by lberne            #+#    #+#             */
/*   Updated: 2024/10/16 23:44:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*let_me_cook(char *ingredients, t_env *env_lst)
{
	t_token	*result;
	char	*temp;
	char	quote;
	int		i;
	int		j;
	
	result = NULL;
	i = 0;
	while (ingredients[i])
	{
		if (!is_wspace(ingredients[i]) || is_special(ingredients[i]))
		{
			temp = (char *)malloc(sizeof(char) * sizeof_token(ingredients, i, env_lst));
			if (!temp)
			{
				perror("Failed allocation in special chop (parsing.c)");
				return (NULL);
			}
			j = 0;
			if (is_special(ingredients[i]))
			{
				temp[j] = ingredients[i];
				i++;
				j++;
				if (temp[j - 1] != '|' && temp[j - 1] == ingredients[i])
				{
					temp[j] = ingredients[i];
					i++;
					j++;
				}
				temp[j] = 0;
			}
			else
			{
				while (!is_wspace(ingredients[i]) && !is_special(ingredients[i]))
				{
					if (is_quote(ingredients[i]))
					{
						quote = ingredients[i];
						temp[j] = ingredients[i];
						i++;
						j++;
						while (ingredients[i] != quote)
						{
							temp[j] = ingredients[i];
							i++;
							j++;
						}
					}
					temp[j] = ingredients[i];
					i++;
					j++;
				}
				temp[j] = 0;
			}
			append_token(&result, create_token(temp, read_type(temp)));
			free(temp);
		}
		if (is_wspace(ingredients[i]))
			i++;
	}
	physio(result);
	return(result);
}
