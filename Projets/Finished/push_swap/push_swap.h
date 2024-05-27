/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:39:47 by tlebon            #+#    #+#             */
/*   Updated: 2024/04/09 17:28:17 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "lib/libft.h"
# include <limits.h>

typedef struct s_node
{
	int				content;

	int				index;
	int				above_median;
	int				push_price;
	struct s_node	*target;

	struct s_node	*next;
}t_node;

// NODES			4	V
t_node		*new_node(int i);
void		nodeadd_front(t_node **nd, t_node *new);
void		nodeadd_back(t_node **nd, t_node *new);
int			node_size(t_node *nd);

// INSTRUCTIONS		5	V
void		swap(t_node **stack, char *name);
void		rotate(t_node **stack, char *name);
void		r_rotate(t_node **stack, char *name);
void		push(t_node **stack1, t_node **stack2, char *name);
void		both(t_node **stack1, t_node **stack2,
				void (*f)(t_node **, char *), char *name);

// SORT				3	v
int			is_sorted(t_node *stack);
void		sort3(t_node **stack);
t_node		*get_lowest(t_node **stack);

//PUSH_SWAP			5	V
int			get_cost(t_node *n, t_node **stack);
void		push_swap(t_node **sa, t_node **sb);

// REFRESH			4	V
void		refresh_index(t_node **sa);
void		refresh_pushprice(t_node **sa, t_node **sb);
t_node		*find_target_asc(t_node *n, t_node **sa);
void		refresh_all(t_node **sa, t_node **sb);

#endif