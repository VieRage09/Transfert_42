/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:11:12 by lberne            #+#    #+#             */
/*   Updated: 2024/10/24 00:24:16 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_token(char *ingr, int start, char *temp)
{
	int	i;
	
	i = 0;
	temp[i] = ingr[start];
	i++;
	start++;
	if (temp[i - 1] != '|' && temp[i - 1] == ingr[start])
	{
		temp[i] = ingr[start];
		i++;
		start++;
	}
	temp[i] = 0;
	return (start);
}

int	handle_normal_token(char *ingr, int start, char *temp)
{
	int		i;
	char	quote;

	i = 0;
	while (!is_wspace(ingr[start]) && !is_special(ingr[start]))
	{
		if (is_quote(ingr[start]))
		{
			quote = ingr[start];
			temp[i] = ingr[start];
			i++;
			start++;
			while (ingr[start] != quote)
			{
				temp[i] = ingr[start];
				i++;
				start++;
			}
		}
		temp[i] = ingr[start];
		i++;
		start++;
	}
	temp[i] = 0;
	return (start);
}

int	chopper(t_token **res, char *ingr, int start)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * ft_strlen(ingr) + 1);
	if (!temp)
		perror("Failed mallocation in chopper (parsing.c)");
	if (is_special(ingr[start]))
		start = handle_special_token(ingr, start, temp);
	else
		start = handle_normal_token(ingr, start, temp);
	append_token(res, create_token(temp, read_type(temp)));
	free(temp);
	return (start);
}

t_token	*let_me_cook(char *ingredients, t_env *env_lst)
{
	t_token	*res;
	int		i;

	res = NULL;
	i = 0;
	while (ingredients[i])
	{
		if (!is_wspace(ingredients[i]) || is_special(ingredients[i]))
		{
			i = chopper(&res, ingredients, i);
		}
		if (ingredients[i] && is_wspace(ingredients[i]))
			i++;
	}
	physio(res);
	tokens_cleaner(res, env_lst);
	if (!ft_strncmp(res->str, "exit", 5))
		exit_(2);
	return (res);
}
