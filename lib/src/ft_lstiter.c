/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:06 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:30 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cursor;

	if (!lst || !(*f))
		return ;
	cursor = lst;
	while (cursor->next != NULL)
	{
		(*f)(cursor->content);
		cursor = cursor->next;
	}
	(*f)(cursor->content);
	return ;
}
