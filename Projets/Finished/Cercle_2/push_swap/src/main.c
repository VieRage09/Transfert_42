/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:39:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/24 16:39:39 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	check_redundancies(t_node *nd)
{
	t_node	*ref;
	t_node	*cursor;

	if (!nd)
		return (0);
	ref = nd;
	while (ref->next)
	{
		cursor = ref->next;
		while (cursor->next)
		{
			if (cursor->content == ref->content)
				return (1);
			cursor = cursor->next;
		}
		if (cursor->content == ref->content)
			return (1);
		ref = ref->next;
	}
	return (0);
}

static int	check_valid(char *s)
{
	int		i;
	long	test;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+')
			return (0);
		if ((s[i] == '-' || s[i] == '+') && ((i != 0 && s[i - 1] != ' ')
				|| !s[i + 1] || !ft_isdigit(s[i + 1])))
			return (0);
		i++;
	}
	test = ft_atol(s);
	if (test < INT_MIN || test > INT_MAX)
		return (0);
	else
		return (1);
}

static void	free_stack(t_node **stack)
{
	t_node	*current;
	t_node	*next;

	if (!*stack)
		return ;
	current = NULL;
	next = *stack;
	while (next)
	{	
		current = next;
		next = current->next;
		free(current);
	}
	return ;
}

static void	menu(int ac, char **av, t_node **stack)
{
	int	i;

	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
		i = 0;
	}
	else
		i = 1;
	while (av[i])
	{
		if (check_valid(av[i]))
			nodeadd_back(stack, new_node(ft_atoi(av[i])));
		else
		{
			free_stack(stack);
			if (ac == 2)
				ft_free_tab((void **)av);
			*stack = NULL;
			return ;
		}
		i++;
	}
	if (ac == 2)
		ft_free_tab((void **)av);
}

int	main(int ac, char *av[])
{
	t_node	*sa;
	t_node	*sb;

	sa = NULL;
	sb = NULL;
	if (ac < 2)
		return (EXIT_FAILURE);
	menu(ac, av, &sa);
	if (!sa || check_redundancies(sa))
	{
		write(2, "Error\n", 6);
		if (sa)
			free_stack(&sa);
		return (EXIT_FAILURE);
	}
	if (node_size(sa) < 4 && !is_sorted(sa))
		sort3(&sa);
	if (!is_sorted(sa))
		push_swap(&sa, &sb);
	free_stack(&sa);
	free_stack(&sb);
	return (EXIT_SUCCESS);
}
