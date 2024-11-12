/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:11:12 by lberne            #+#    #+#             */
/*   Updated: 2024/11/06 16:18:20 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return the number of bytes the char is coded with
(needed to handle non-ascii char)*/
int	utf8_char_len(unsigned char c)
{
	if ((c & 0x80) == 0)
		return (1);
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (3);
	if ((c & 0xF8) == 0xF0)
		return (4);
	return (1);
}

/* handle | << < >> and > */
int	handle_special_token(char *ingr, int start, char *temp)
{
	int	i;
	int	char_len;

	i = 0;
	char_len = utf8_char_len(ingr[start]);
	while (char_len-- > 0)
		temp[i++] = ingr[start++];
	if (temp[i - 1] != '|' && temp[i - 1] == ingr[start])
	{
		char_len = utf8_char_len(ingr[start]);
		while (char_len-- > 0)
			temp[i++] = ingr[start++];
	}
	temp[i] = '\0';
	return (start - 1);
}

int	handle_normal_token(char *ingr, int start, char *temp)
{
	int		i;
	char	quote;
	int		char_len;

	i = 0;
	while (!is_wspace(&ingr[start], utf8_char_len(ingr[start]))
		&& !is_special(&ingr[start], utf8_char_len(ingr[start])))
	{
		if (is_quote(&ingr[start], utf8_char_len(ingr[start])))
		{
			quote = ingr[start];
			temp[i++] = ingr[start++];
			while (ingr[start] && ingr[start] != quote)
			{
				char_len = utf8_char_len(ingr[start]);
				while (char_len-- > 0)
					temp[i++] = ingr[start++];
			}
			if (ingr[start] == quote)
				temp[i++] = ingr[start++];
		}
		else
		{
			char_len = utf8_char_len(ingr[start]);
			while (char_len-- > 0)
				temp[i++] = ingr[start++];
		}
	}
	temp[i] = '\0';
	return (start - 1);
}

int	chopper(t_token **res, char *ingr, int start)
{
	char	*temp;
	int		char_len;

	temp = (char *)malloc(sizeof(unsigned char) * (ft_strlen(ingr) + 1));
	if (!temp)
		return (0);
	temp[0] = '\0';
	if (is_special(&ingr[start], utf8_char_len(ingr[start])))
		start = handle_special_token(ingr, start, temp);
	else
		start = handle_normal_token(ingr, start, temp);
	append_token(res, create_token(temp, read_type(temp)));
	free(temp);
	return (start);
}

t_token	*let_me_cook(char *ingredients, t_data *data)
{
	int		i;
	t_token	*res;
	int		char_len;

	i = 0;
	res = NULL;
	while (ingredients[i])
	{
		char_len = utf8_char_len(ingredients[i]);
		if (!is_wspace(&ingredients[i], char_len)
			|| is_special(&ingredients[i], char_len))
			i = chopper(&res, ingredients, i);
		if (is_wspace(&ingredients[i], char_len))
			i += char_len;
		else
			i++;
	}
	physio(res);
	finishes(res, *data);
	if (ft_exit(res, data))
	{
		free_tokens(res);
		return (NULL);
	}
	return (res);
}
