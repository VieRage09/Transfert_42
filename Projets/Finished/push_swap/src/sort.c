/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 02:38:26 by tlebon            #+#    #+#             */
/*   Updated: 2024/04/09 17:28:09 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// Checks if the stack is sorted
int	is_sorted(t_node *stack)
{
	t_node	*cursor;
	int		max;

	if (!stack)
		return (0);
	cursor = stack;
	max = cursor->content;
	while (cursor->next)
	{
		cursor = cursor->next;
		if (cursor->content > max)
			max = cursor->content;
		else
			return (0);
	}
	return (1);
}

// Sorts a 3 node stack
void	sort3(t_node **stack)
{
	t_node	*highest;
	t_node	*cursor;
	int		max;

	highest = *stack;
	cursor = *stack;
	max = cursor->content;
	while (cursor->next)
	{
		cursor = cursor->next;
		if (cursor->content > max)
		{
			max = cursor->content;
			highest = cursor;
		}
	}
	if (*stack == highest)
		rotate(stack, "ra");
	else if ((*stack)->next == highest)
		r_rotate(stack, "rra");
	if ((*stack)->content > (*stack)->next->content)
		swap(stack, "sa");
}

// Returns a pointer to the node with the lowest content of the stack
t_node	*get_lowest(t_node **stack)
{
	t_node	*curs;
	t_node	*lowest;
	int		min;

	curs = *stack;
	lowest = NULL;
	min = INT_MAX;
	while (curs)
	{
		if (curs->content < min)
		{
			min = curs->content;
			lowest = curs;
		}
		curs = curs->next;
	}
	return (lowest);
}
