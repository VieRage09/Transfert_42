/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:19 by lberne            #+#    #+#             */
/*   Updated: 2024/10/16 21:54:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check si il y a une correspondance entre le $ dans l'input et la liste de env
//puis renvoie la taille (0 si pas de correspondance donc)
size_t	sizeof_env(char *ingr, int start, t_env *env_lst)
{
	char	*name;
	int		i;
	t_env	*current;
	
	name = (char *)malloc(sizeof(char) * ft_strlen(ingr) + 1);
	i = 0;
	current = env_lst;
	start++; //pour passer le $
	while (!is_wspace(ingr[start]) && !is_special(ingr[start]) && !is_quote(ingr[start]))
	{
		name[i] = ingr[start];
		i++;
		start++;
	}
	name[i] = 0;
	while (current != NULL)
	{
		if (!ft_strncmp(current->name, name, i))
			return (ft_strlen(current->str));
		current = current->next;
	}
	return (0);
}

size_t	sizeof_token(char *ingr, int start, t_env *env_lst)
{
		size_t	res;
		int		tmp;

		res = 0;
		tmp = start;
		while (ingr[tmp] && !is_wspace(ingr[tmp]) && !is_special(ingr[tmp]))
		{
			while (is_quote(ingr[tmp]))
			{
				res++;
				tmp++;
			}
			res++;
			tmp++;
		}
		while (start <= tmp)
		{
			if (ingr[start] == '$')
				res += sizeof_env(ingr, start, env_lst);
			start++;	
		}
		return (res + 1);
}

char	*get_env(char *token, int start, t_env *env_lst)
{
	char	*name;
	int		i;
	t_env	*current;
	
	name = (char *)malloc(sizeof(char) * ft_strlen(token) + 1);
	i = 0;
	current = env_lst;
	start++; //pour passer le $
	while (!is_wspace(token[start]) && !is_special(token[start]) && !is_quote(token[start]))
	{
		name[i] = token[start];
		i++;
		start++;
	}
	name[i] = 0;
	while (current != NULL)
	{
		if (!ft_strncmp(current->name, name, i))
			return (current->str);
		current = current->next;
	}
	return (NULL);
}

void	tokens_cleaner(t_token *tokens_head, t_env *env_head)
{
	t_token	*current_token;
	char	*new_str;
	int		i;
	int		j;
	
	current_token = tokens_head;
	while (current_token)
	{
		if (current_token->hello_there == true)
		{
			i = 0;
			j = 0;
			new_str = (char *)malloc(sizeof(char) * sizeof_token(current_token->str, 0, env_head) + 1);
			while (current_token->str[i])
			{
				if (!is_quote(current_token->str[i]) && current_token->str[i] != '$')
				{
					new_str[j] = current_token->str[i];
					i++;
					j++;
				}
				if (current_token->str[i] == 39) //ignorer entre ' '
				{
					i++;
					while (current_token->str[i] != 39)
					{
						new_str[j] = current_token->str[i];
						i++;
						j++;
					}
					i++;
				}
				if (current_token->str[i] == '$')
				{
					if (get_env(current_token->str, i, env_head))
						j = ft_strlcat(new_str, get_env(current_token->str, i, env_head), sizeof_token(current_token->str, 0, env_head));
					while(current_token->str[i] && !is_quote(current_token->str[i]))
						i++;
				}
				if (current_token->str[i] == 34)
					i++;
			}
			new_str[j] = 0;
			current_token->str = new_str;
		}
		current_token = current_token->next;
	}
}
