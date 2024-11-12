/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:19 by lberne            #+#    #+#             */
/*   Updated: 2024/11/06 16:01:47 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*copy the normal stuff without changes*/
int	handle_normal(char *str, char *new_str, int start)
{
	int		i;

	i = ft_strlen(new_str);
	while (str[start] && !is_quote(&str[start], utf8_char_len(str[start]))
		&& str[start] != '$')
	{
		new_str[i] = str[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (start);
}

/*replace the $*/
int	handle_dollars(char *str, char *new_str, int start, t_data data)
{
	char	*env;

	start++;
	env = get_env(str, start, data.env_lst);
	if ((is_wspace(&str[start], utf8_char_len(str[start]))
			|| is_quote(&str[start], utf8_char_len(str[start]))))
	{
		ft_cat(new_str, NULL, '$');
		if (str[start] && !is_quote(&str[start], utf8_char_len(str[start])))
			start++;
	}
	else if (str[start] == '?' )
	{
		ft_cat(new_str, ft_itoa(data.ret), 0);
		start++;
	}
	else
	{
		ft_cat(new_str, env, 0);
		if (str[start] == '$')
			start++;
		else
		{
			while (!is_quote(&str[start], utf8_char_len(str[start]))
				&& str[start] != '$'
				&& !is_wspace(&str[start], utf8_char_len(str[start])))
				start++;
		}
	}
	return (start);
}

/*get rid of quotes the proper way ('' or "")*/
int	handle_quotes(char *str, char *new_str, int start, t_data data)
{
	if (str[start] == 39)
	{
		start++;
		while (str[start] != 39)
		{
			ft_cat(new_str, NULL, str[start]);
			start++;
		}
	}
	else if (str[start] == 34)
	{
		start++;
		while (str[start] != 34)
		{
			if (str[start] == '$')
				start = handle_dollars(str, new_str, start, data);
			else
			{
				ft_cat(new_str, NULL, str[start]);
				start++;
			}
		}
	}
	new_str[ft_strlen(new_str)] = '\0';
	return (start + 1);
}

/*simply needed because norm is stupid*/
int	handle_clean(char *str, char *new_str, int start, t_data data)
{
	if (!str || !new_str || !data.env_lst)
		return (0);
	if (!is_quote(&str[start], utf8_char_len(str[start])) && str[start] != '$')
		start = handle_normal(str, new_str, start);
	else if (is_quote(&str[start], utf8_char_len(str[start])))
		start = handle_quotes(str, new_str, start, data);
	else if (str[start] == '$')
		start = handle_dollars(str, new_str, start, data);
	return (start);
}

/*finishes handle quotes and $ replacements by replacing old str
by a fully interpreted token, hello there is a flag that indicate that either
a quote or a $ has been found during parsing*/
void	finishes(t_token *tokens, t_data data)
{
	t_token	*current_token;
	char	*new_str;
	int		new_len;
	int		i;

	current_token = tokens;
	while (current_token)
	{
		if (current_token->hello_there == true)
		{
			new_len = token_len(current_token->str, data.env_lst);
			new_str = (char *)malloc(sizeof(unsigned char) * (new_len + 1));
			if (!new_str)
				return ;
			new_str[0] = '\0';
			i = 0;
			while (current_token->str[i])
				i = handle_clean(current_token->str, new_str, i, data);
			new_str[ft_strlen(new_str)] = '\0';
			free(current_token->str);
			current_token->str = new_str;
		}
		current_token = current_token->next;
	}
}
