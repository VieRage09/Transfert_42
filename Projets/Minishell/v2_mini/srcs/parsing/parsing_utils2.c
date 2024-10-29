/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:19 by lberne            #+#    #+#             */
/*   Updated: 2024/10/29 18:07:37 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	match(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (false);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (!s1[i] && !s2[i])
		return (true);
	return (false);
}

void	ft_strcat(char *dest, const char *src)
{
	int		i;
	int		j;

	if (!src || !dest)
		return ;
	j = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

char	*get_env(char *token, int start, t_env *env_lst)
{
	char	*name;
	int		i;
	t_env	*current;
	
	if (!token)
		return (NULL);
	name = (char *)malloc(sizeof(char) * ft_strlen(token) + 1);
	if (!name)
		return (NULL);
	name[0] = '\0';
	i = 0;
	current = env_lst;
	while (!is_wspace(token[start]) && !is_quote(token[start]) && token[start] != '$')
		name[i++] = token[start++];
	name[i] = '\0';
	while (current)
	{
		if (match(name, current->name))
		{
			free(name);
			return (current->str);
		}
		current = current->next;
	}
	free(name);
	return (NULL);
}

int	token_len(char *token, t_env *env_lst)
{
		size_t	res;
		int		i;
		char	*env;

		if (!token)
			return (0);
		res = ft_strlen(token);
		i = 0;
		while (token[i])
		{
			if (token[i] == '$') //strlen DOIT renvoyer 0 si s = NULL
			{
				env = get_env(token, i + 1, env_lst);
				if (env)
					res += ft_strlen(env);
			}
			i++;
		}
		return (res);
}

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

// int	handle_dollars(char *str, char *new_str, int start, t_env *env_lst)
// {
// 	start++;
// 	if (is_wspace(str[start]) || is_quote(str[start]))
// 	{
// 		ft_strcat(new_str, "$");
// 		if (!is_quote(str[start]))
// 			start++;
// 	}
// 	else if (str[start] == '?')
// 	{
// 		ft_strcat(new_str, ft_itoa(env_lst->ret));
// 		start++;
// 	}
// 	else
// 		ft_strcat(new_str, get_env(str, start, env_lst));
// 		if (str[start] == '$')
// 			start++;
// 		else
// 		{
// 			while (!is_quote(str[start]) && str[start] != '$' && !is_wspace(str[start]))
// 				start++;
// 		}
// 	return (start);
// }

int	handle_dollars(char *str, char *new_str, int start, t_env *env_lst)
{
	char	*env;

	start++;
	env = get_env(str, start, env_lst);
	if (new_str && (is_wspace(str[start]) || is_quote(str[start])))
	{
		ft_strcat(new_str, "$");
		if (!is_quote(str[start]))
			start++;
	}
	else if (env && new_str && str[start] == '?' )
	{
		ft_strcat(new_str, ft_itoa(env_lst->ret));
		start++;
	}
	else if (env && new_str)
	{
		ft_strcat(new_str, env);
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
	int	i;
	
	i = ft_strlen(new_str);
	if (str[start] == 39) //ignorer entre ' '
	{
		start++;
		while (str[start] != 39)
		{
			new_str[i] = str[start];
			i++;
			start++;
		}
	}
	else if (str[start] == 34)
	{
		start++;
		while (str[start] != 34)
		{
			if (str[start] == '$')
				start = handle_dollars(str, new_str, start++, env_lst);
			else
			{
				new_str[i] = str[start];
				i++;
				start++;
			}
		}
	}
	new_str[i] = '\0';
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

void	tokens_cleaner(t_token *tokens, t_env *env_lst)
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
