/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:32:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 19:14:12 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str_tab(char **tab)
{
	if (!tab)
		return (1);
	while (*tab)
	{
		ft_putstr(*tab);
		ft_putstr("\n");
		(tab)++;
	}
	ft_putstr("\n");
	return (0);
}
