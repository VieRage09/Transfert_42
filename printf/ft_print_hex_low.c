/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_low.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:13:34 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/05 13:54:45 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

static int	count_digit(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= (-1);
		count++;
	}
	while (n > 15)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static char	write_hex(long n)
{
	if (n > 15)
		return ('\0');
	else if (n > 9)
		return (n + 'a' - 10);
	else
		return (n + '0');
}

int	ft_print_hex_low(int i)
{
	char			*s;
	int				cursor;
	unsigned int	nbr;

	nbr = (unsigned int) i;
	s = malloc((count_digit(nbr) + 1) * sizeof(char));
	if (!s)
		return (-1);
	cursor = count_digit(nbr) - 1;
	s[cursor + 1] = '\0';
	while (nbr > 15)
	{
		s[cursor] = write_hex(nbr % 16);
		nbr /= 16;
		cursor--;
	}
	s[cursor] = write_hex(nbr);
	cursor = ft_strlen(s);
	write(1, s, cursor);
	free(s);
	return (cursor);
}
