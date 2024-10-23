/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:29:04 by tlebon            #+#    #+#             */
/*   Updated: 2024/10/23 19:54:16 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Iterates over str
// If the first char is not - and/or 1 of the following char is not an n
// returns false
// Otherwise returns true
static int	valid_arg(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!str[0] || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}


// TODO : Pouvoir differencier un arg entre quote d'un arg sans
int	exec_echo(char **cmd_tab)
{
	int	i;

	if (!cmd_tab)
		return (1);
	i = 1;
	while (cmd_tab[i] && valid_arg(cmd_tab[i]))
		++i;
	if (i == 1)
	{
		while (cmd_tab[i])
		{
			ft_putstr(cmd_tab[i]);
			write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
	else
	{
		while (cmd_tab[i])
		{
			ft_putstr(cmd_tab[i]);
			write(1, " ", 1);
			i++;
		}
	}
	printf("Echo returned\n");	
	return (0);
}
