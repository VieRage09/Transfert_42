/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:01:35 by tlebon            #+#    #+#             */
/*   Updated: 2024/05/30 19:47:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_print_int(int n)
{
	char	*s;
	int		size;

	s = ft_itoa(n);
	if (!s)
		return (-1);
	size = ft_strlen(s);
	write(1, s, size);
	free(s);
	return (size);
}
