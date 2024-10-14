/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:11:12 by lberne            #+#    #+#             */
/*   Updated: 2024/10/14 21:41:22 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*detailled_chop(char *ingr, int step) //ignore $ for now
{
	char	*res;
	int		i;
	char	quote;

	//quote = 0;
	res = (char *)malloc(sizeof(char) * subtil(ingr) + 1);
	if (!res)
	{
		perror("Failed allocation in detailled chop (parsing.c)");
		return (NULL);
	}
	i = 0;
	while (!is_wspace(ingr[step]) && !is_special(ingr[step]))
	{
		if (is_quote(ingr[step]))
		{
			quote = ingr[step];
			//step++;
			while (ingr[step] != quote)
			{
				res[i] = ingr[step];
				step++;
				i++;
			}
			//step++;
			//continue ;
		}
		//if (!is_wspace(ingr[step]) && !is_special(ingr[step]))
		res[i] = ingr[step];
		step++;
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*special_chop(char *ingr, int step)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * subtil(ingr) + 1);
	if (!res)
	{
		perror("Failed allocation in special chop (parsing.c)");
		return (NULL);
	}
	i = 0;
	res[i] = ingr[step];
	if (ingr[step] != '|' && ingr[step] == ingr[step + 1])
	{
		i++;
		res[i] = ingr[step + 1];
	}
	i++;
	res[i] = 0;
	return (res);
}

char	*chop(char *ingredients, int step)
{
	int		i;
	char	*quote;
	char	*fruit;
	
	i = 0;
	if (is_special(ingredients[step]))
		fruit = special_chop(ingredients, step);
	else
		fruit = detailled_chop(ingredients, step);
	return (fruit);
}

// t_token	*let_me_cook(char *ingredients)
// {
// 	t_token	*result;
// 	char	*temp;
// 	bool	next_is_cmd;
// 	int		i;
	
// 	result = NULL;
// 	i = 0;
// 	next_is_cmd = true;
// 	while (ingredients[i])
// 	{
// 		if (!is_wspace(ingredients[i]))
// 		{
// 			temp = chop(ingredients, i); //token en entier moins les quotes et $ remplaces
// 			if (next_is_cmd && !is_special(temp[0]))
// 			{
// 				append_token(&result, create_token(temp, CMD));
// 				next_is_cmd = false;
// 			}
// 			else
// 				append_token(&result, create_token(temp, read_type(temp)));
// 			if (!ft_strncmp(temp, "|", 1))
// 				next_is_cmd = true;
// 			i = end_of_token(ingredients, i); //dernier char du token
// 			free(temp);
// 		}
// 		i++;
// 	}
// 	return(result);
// }

t_token	*let_me_cook(char *ingredients)
{
	t_token	*result;
	char	*temp;
	char	quote;
	int		i;
	int		j;
	
	result = NULL;
	temp = (char *)malloc(sizeof(char) * subtil(ingredients) + 1);
	if (!temp)
	{
		perror("Failed allocation in special chop (parsing.c)");
		return (NULL);
	}
	i = 0;
	while (ingredients[i])
	{
		if (!is_wspace(ingredients[i]) || is_special(ingredients[i]))
		{
			clear_str(temp);
			j = 0;
			if (is_special(ingredients[i]))
			{
				temp[j] = ingredients[i];
				i++;
				j++;
				if (ingredients[j - 1] != '|' && ingredients[j - 1] == ingredients[i])
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
		}
		if (is_wspace(ingredients[i]))
			i++;
	}
	free(temp);
	physio(result);
	return(result);
}
