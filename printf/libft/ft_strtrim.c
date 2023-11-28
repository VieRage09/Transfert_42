/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:21:54 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/24 17:56:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static size_t	find_start(char const *s, char const *set)
{
	size_t	i;
	size_t	p;

	i = 0;
	while (s[i])
	{
		p = 0;
		while (set[p])
		{
			if (s[i] == set[p])
				break ;
			p++;
		}
		if (p == ft_strlen(set))
			return (i);
		i++;
	}
	return (0);
}

static size_t	find_end(char const *s, char const *set)
{
	size_t	i;
	size_t	p;

	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		p = 0;
		while (set[p])
		{
			if (s[i] == set[p])
				break ;
			p++;
		}
		if (p == ft_strlen(set))
			return (i);
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*trim;
	size_t	i;

	if (!s || !set)
		return (NULL);
	if (find_end(s, set) == 0)
		trim = malloc(1);
	else
		trim = malloc((find_end(s, set) - find_start(s, set) + 2));
	if (trim == NULL)
		return (NULL);
	if (find_end(s, set) == 0)
	{
		trim[0] = '\0';
		return (trim);
	}
	i = 0;
	while (i < find_end(s, set) - find_start(s, set) + 1)
	{
		trim[i] = s[i + find_start(s, set)];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
