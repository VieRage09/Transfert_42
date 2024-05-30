/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:31 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*cursor;

	if (!lst)
		return (0);
	size = 1;
	cursor = lst;
	while (cursor->next != NULL)
	{
		size++;
		cursor = cursor->next;
	}
	return (size);
}
