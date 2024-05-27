/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:04:48 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/22 16:08:00 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// Finds and returns the nodes of the stack that has the cheapest push price
static t_node	*find_cheapest(t_node **stack)
{
	t_node	*curs;
	t_node	*target;
	int		cheapest;

	curs = *stack;
	target = NULL;
	cheapest = INT_MAX;
	while (curs)
	{
		if (curs->push_price < cheapest)
		{
			cheapest = curs->push_price;
			target = curs;
		}
		curs = curs->next;
	}
	return (target);
}

// Rotates sa and sb until cheapest and cheapest target are topped
// Cheapest must be inside stack1
static void	end_rotation(t_node **stack1, t_node **stack2, t_node *cheapest)
{
	if (*stack1 != cheapest)
	{
		if (cheapest->above_median)
			rotate(stack1, "rb");
		else if (*stack1 != cheapest && !cheapest->above_median)
			r_rotate(stack1, "rrb");
	}
	else if (*stack2 != cheapest->target)
	{
		if (cheapest->target->above_median)
			rotate(stack2, "ra");
		else if (*stack2 != cheapest->target && !cheapest->target->above_median)
			r_rotate(stack2, "rra");
	}
}

// Rotates the stacks accordingly 
// then push the cheapest node from stack1 to stack2
// Print the operations
static void	push_cheapest(t_node **stack1, t_node **stack2)
{
	t_node	*cheapest;

	cheapest = find_cheapest(stack1);
	while (*stack1 != cheapest || *stack2 != cheapest->target)
	{
		if (!(*stack1 == cheapest || *stack2 == cheapest->target)
			&& cheapest->above_median && cheapest->target->above_median)
		{
			both(stack2, stack1, rotate, "rr");
			refresh_index(stack2);
			refresh_index(stack1);
		}
		else if (!(*stack1 == cheapest || *stack2 == cheapest->target)
			&& !cheapest->above_median && !cheapest->target->above_median)
		{
			both(stack2, stack1, r_rotate, "rrr");
			refresh_index(stack2);
			refresh_index(stack1);
		}
		else
			end_rotation(stack1, stack2, cheapest);
	}
	push(stack1, stack2, "pa");
	return ;
}

// Returns the number of operations needed to top the node n
int	get_cost(t_node *n, t_node **stack)
{
	if (n->index < 1 + node_size(*stack) / 2 && n->above_median)
		return (n->index);
	else
		return (node_size(*stack) - n->index);
}

// Sorting loop :
// Pushes everything to sb until it remains 3 nodes in sa
// Then sort sa and loops on refresh_all then push_cheapest while sb exists
void	push_swap(t_node **sa, t_node **sb)
{
	while (node_size(*sa) > 3)
		push(sa, sb, "pb");
	sort3(sa);
	while (*sb)
	{
		refresh_all(sa, sb);
		push_cheapest(sb, sa);
	}
	while (!is_sorted(*sa))
	{
		refresh_all(sa, sb);
		if (get_lowest(sa)->above_median)
			rotate(sa, "ra");
		else
			r_rotate(sa, "rra");
	}
}
