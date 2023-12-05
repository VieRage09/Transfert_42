/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:04:55 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/05 14:21:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static char	write_hex(unsigned long n)
{
	if (n > 15)
		return ('\0');
	else if (n > 9)
		return (n + 'a' - 10);
	else
		return (n + '0');
}

int	ft_print_pointer(void *p)
{
	unsigned long	adr;

	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	adr = (unsigned long)p;
	write(1, "0x", 2);


	return (0);
}
