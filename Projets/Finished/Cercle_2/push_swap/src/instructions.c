/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:14:38 by tlebon            #+#    #+#             */
/*   Updated: 2024/04/09 17:41:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

// Swaps the first two elements of stack
// Prints name if not NULL
void	swap(t_node **stack, char *name)
{
	t_node	*tmp;

	if (!*stack || node_size(*stack) < 2)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	tmp->next = *stack;
	*stack = tmp;
	if (name)
		ft_printf("%s\n", name);
	return ;
}

// Rotates stack -> the first element is now the last 
// Prints name if not NULL
void	rotate(t_node **stack, char *name)
{
	t_node	*tmp;

	if (!*stack || node_size(*stack) < 2)
		return ;
	tmp = (*stack);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *stack;
	*stack = (*stack)->next;
	tmp->next->next = NULL;
	if (name)
		ft_printf("%s\n", name);
	return ;
}

// Reverse rotates stack -> the last element is now the first
// Prints name if not NULL
void	r_rotate(t_node **stack, char *name)
{
	t_node	*tmp1;
	t_node	*tmp2;

	if (!*stack || node_size(*stack) < 2)
		return ;
	tmp1 = (*stack);
	tmp2 = NULL;
	while (tmp1->next)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (tmp2)
		tmp2->next = NULL;
	tmp1->next = *stack;
	*stack = tmp1;
	if (name)
		ft_printf("%s\n", name);
	return ;
}

// Removes the first element of stack1 and put it at the top of stack2
// Prints name if not NULL
void	push(t_node **stack1, t_node **stack2, char *name)
{
	t_node	*tmp;		

	if (!*stack1)
		return ;
	tmp = *stack1;
	*stack1 = tmp->next;
	if (!*stack2)
	{
		*stack2 = new_node(tmp->content);
		free(tmp);
	}
	else
		nodeadd_front(stack2, tmp);
	if (name)
		ft_printf("%s\n", name);
	return ;
}

// Applies function f on both stacks (f can be swap, rotate or r_rotate)
// Prints name if not NULL
void	both(t_node **stack1, t_node **stack2,
	void (*f)(t_node **, char *), char *name)
{
	if (!*stack1 || !*stack2 || !(*f))
		return ;
	(*f)(stack1, NULL);
	(*f)(stack2, NULL);
	if (name)
		ft_printf("%s\n", name);
	return ;
}
