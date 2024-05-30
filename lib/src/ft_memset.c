/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:54:00 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:55 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	ch;
	char			*ptr;
	size_t			i;

	ptr = s;
	ch = c;
	i = 0;
	while (i < n)
	{
		ptr[i++] = ch;
	}
	return (s);
}
