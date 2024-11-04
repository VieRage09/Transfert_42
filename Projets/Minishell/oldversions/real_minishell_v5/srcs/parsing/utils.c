/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:53:26 by lberne            #+#    #+#             */
/*   Updated: 2024/10/30 16:31:20 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_cat(char *dest, const char *src, const char c_src)
{
	int		i;
	int		j;

	if (!dest)
		return ;
	j = ft_strlen(dest);
	if (!c_src && src)
	{
		i = 0;
		while (src[i])
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
	else if (!src && c_src)
	{
		dest[j] = c_src;
		j++;
	}
	dest[j] = '\0';
}
