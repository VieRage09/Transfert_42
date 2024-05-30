/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:00:41 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:45:49 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	cur;

	i = 0;
	if (small[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i])
	{
		if (big[i] == small[0])
		{
			cur = 0;
			while (small[cur] && i + cur < len)
			{
				if (big[i + cur] != small[cur])
					break ;
				cur++;
			}
			if (cur == ft_strlen(small))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
