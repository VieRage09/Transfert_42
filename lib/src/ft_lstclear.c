/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:54:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:42:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cursor;
	t_list	*buffer;

	if (!lst || !(*del))
		return ;
	cursor = *lst;
	while (cursor->next != NULL)
	{
		buffer = cursor;
		cursor = cursor->next;
		(*del)(buffer->content);
		free(buffer);
	}
	(*del)(cursor->content);
	free(cursor);
	*lst = NULL;
	return ;
}
