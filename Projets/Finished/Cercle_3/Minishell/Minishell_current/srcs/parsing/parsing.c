/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:11:12 by lberne            #+#    #+#             */
/*   Updated: 2024/11/27 20:34:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_normal_norm(int *i_ptr, char *ingr, int *start_ptr, char *temp)
{
	int	char_len;

	char_len = utf8_char_len(ingr[*start_ptr]);
	while (char_len-- > 0)
		temp[(*i_ptr)++] = ingr[(*start_ptr)++];
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
				handle_normal_norm(&i, ingr, &start, temp);
			if (ingr[start] == quote)
				temp[i++] = ingr[start++];
		}
		else
			handle_normal_norm(&i, ingr, &start, temp);
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

int	let_me_cook(t_data *data)
{
	int		i;
	int		char_len;

	i = 0;
	while (data->line[i])
	{
		char_len = utf8_char_len(data->line[i]);
		if (!is_wspace(&data->line[i], char_len)
			|| is_special(&data->line[i], char_len))
			i = chopper(&data->tokens, data->line, i);
		if (is_wspace(&data->line[i], char_len))
			i += char_len;
		else
			i++;
	}
	physio(data->tokens);
	finishes(data->tokens, *data);
	// if (ft_exit(data->tokens, data))
	// 	return (0);
	return (1);
}
