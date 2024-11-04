/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:19 by lberne            #+#    #+#             */
/*   Updated: 2024/10/30 16:33:45 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_normal(char *str, char *new_str, int start)
{
	int		i;

	i = ft_strlen(new_str);
	while (str[start] && !is_quote(str[start]) && str[start] != '$')
	{
		new_str[i] = str[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (start);
}

int	handle_dollars(char *str, char *new_str, int start, t_env *env_lst)
{
	char	*env;

	start++;
	env = get_env(str, start, env_lst);
	if ((is_wspace(str[start]) || is_quote(str[start])))
	{
		ft_cat(new_str, NULL, '$');
		if (str[start] && !is_quote(str[start]))
			start++;
	}
	else if (str[start] == '?' )
	{
		ft_cat(new_str, ft_itoa(env_lst->ret), 0);
		start++;
	}
	else
	{
		ft_cat(new_str, env, 0);
		if (str[start] == '$')
			start++;
		else
		{
			while (!is_quote(str[start]) && str[start] != '$' && !is_wspace(str[start]))
				start++;
		}
	}
	return (start);
}

int	handle_quotes(char *str, char *new_str, int start, t_env *env_lst)
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
				start = handle_dollars(str, new_str, start, env_lst);
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

int	handle_clean(char *str, char *new_str, int start, t_env *env_lst)
{
	if (!str || !new_str || !env_lst)
		return (0);
	if (!is_quote(str[start]) && str[start] != '$')
		start = handle_normal(str, new_str, start);
	else if (is_quote(str[start]))
		start = handle_quotes(str, new_str, start, env_lst);
	else if (str[start] == '$')
		start = handle_dollars(str, new_str, start, env_lst);
	return (start);
}

void	finishes(t_token *tokens, t_env *env_lst)
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
			new_len = token_len(current_token->str, env_lst);
			new_str = (char *)malloc(sizeof(char) * (new_len + 1));
			if (!new_str)
				return ;
			new_str[0] = '\0';
			i = 0;
			while (current_token->str[i])
				i = handle_clean(current_token->str, new_str, i, env_lst);
			new_str[ft_strlen(new_str)] = '\0';
			free(current_token->str);
			current_token->str = new_str;
		}
		current_token = current_token->next;
	}
}
