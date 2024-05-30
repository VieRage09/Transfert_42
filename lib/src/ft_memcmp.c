/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:00:08 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:44 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*mem1;
	unsigned char	*mem2;

	i = 0;
	mem1 = (unsigned char *) s1;
	mem2 = (unsigned char *) s2;
	while (i < n)
	{
		if (mem1[i] > mem2[i])
			return ((unsigned int)(mem1[i] - mem2[i]));
		if (mem1[i] < mem2[i])
			return ((unsigned int)(mem1[i] - mem2[i]));
		i++;
	}
	return (0);
}
