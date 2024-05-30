/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:20 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cursor;
	t_list	*new_lst;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	new_lst = ft_lstnew((*f)(lst->content));
	if (!new_lst)
		return (NULL);
	cursor = lst;
	if (cursor->next == NULL)
		return (new_lst);
	cursor = cursor->next;
	while (cursor->next != NULL)
	{
		ft_lstadd_back(&new_lst, ft_lstnew((*f)(cursor->content)));
		cursor = cursor->next;
	}
	ft_lstadd_back(&new_lst, ft_lstnew((*f)(cursor->content)));
	return (new_lst);
}
