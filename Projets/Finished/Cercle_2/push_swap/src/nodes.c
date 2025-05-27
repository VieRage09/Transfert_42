/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:24:42 by tlebon            #+#    #+#             */
/*   Updated: 2024/04/09 17:30:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// Creates a new node, initializes the content value to i and the other to NULL
// or -1
t_node	*new_node(int i)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->content = i;
	n->index = -1;
	n->above_median = -1;
	n->push_price = -1;
	n->target = NULL;
	n->next = NULL;
	return (n);
}

// Adds node new at the beggining of list nd
void	nodeadd_front(t_node **nd, t_node *new)
{
	if (!new)
		return ;
	if (!*nd)
	{	
		*nd = new;
		return ;
	}
	new->next = *nd;
	*nd = new;
	return ;
}

// Adds node new at the end of list nd
void	nodeadd_back(t_node **nd, t_node *new)
{
	t_node	*cursor;

	if (!new)
		return ;
	if (!*nd)
	{	
		*nd = new;
		return ;
	}
	cursor = *nd;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
	return ;
}

// Returns the number of nodes contained in list nd
int	node_size(t_node *nd)
{
	int		size;
	t_node	*cursor;

	if (!nd)
		return (0);
	size = 1;
	cursor = nd;
	while (cursor->next)
	{
		size++;
		cursor = cursor->next;
	}
	return (size);
}
