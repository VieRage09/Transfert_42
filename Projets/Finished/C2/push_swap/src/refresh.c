/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 04:20:37 by tlebon            #+#    #+#             */
/*   Updated: 2024/04/09 17:26:11 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// Refreshes the index and the boolean above_median of
// all the nodes of both stacks
void	refresh_index(t_node **stack)
{
	t_node	*curs;
	int		index;

	curs = *stack;
	index = 0;
	while (curs)
	{
		curs->index = index;
		if (index < (node_size(*stack) + 1) / 2)
			curs->above_median = 1;
		else
			curs->above_median = 0;
		index++;
		curs = curs->next;
	}
	return ;
}

// Refreshes the pushprice value of the nodes of stack sb
void	refresh_pushprice(t_node **sa, t_node **sb)
{
	t_node	*curs;

	curs = *sb;
	while (curs)
	{
		if (curs->above_median && curs->target->above_median)
		{
			if (curs->index > curs->target->index)
				curs->push_price = curs->index;
			else
				curs->push_price = curs->target->index;
		}
		else if ((!(curs->above_median) && !(curs->target->above_median)))
		{
			if (node_size(*sb) - curs->index
				> node_size(*sa) - curs->target->index)
				curs->push_price = node_size(*sb) - curs->index;
			else
				curs->push_price = node_size(*sa) - curs->target->index;
		}
		else
			curs->push_price = get_cost(curs, sb) + get_cost(curs->target, sa);
		curs = curs->next;
	}
	return ;
}

// Finds the node of sa that has the smallest bigger content compared to
// n content and returns its adress
t_node	*find_target_asc(t_node *n, t_node **sa)
{
	t_node	*curs;
	t_node	*target;
	long	max;

	curs = *sa;
	target = NULL;
	max = LONG_MAX;
	while (curs)
	{
		if (curs->content > n->content && (long)curs->content < max)
		{
			max = (long)curs->content;
			target = curs;
		}
		curs = curs->next;
	}
	if (!target)
		target = get_lowest(sa);
	return (target);
}

// Refreshes the target pointer of all the nodes of stack sb
// Target pointer of node x now points to the node of sa that has the smallest
// bigger content compared to x content, then refreshes everything else
void	refresh_all(t_node **sa, t_node **sb)
{
	t_node	*bcurs;

	bcurs = *sb;
	while (bcurs)
	{
		bcurs->target = find_target_asc(bcurs, sa);
		bcurs = bcurs->next;
	}
	refresh_index(sa);
	refresh_index(sb);
	refresh_pushprice(sa, sb);
	return ;
}
