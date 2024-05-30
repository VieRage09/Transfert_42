/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:32:37 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:43:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_str_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		ft_putstr(*tab);
		ft_putstr("\n");
		(tab)++;
	}
	return ;
}
