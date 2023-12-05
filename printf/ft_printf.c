/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:11:47 by tlebon            #+#    #+#             */
/*   Updated: 2023/12/05 15:50:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"
#include <stdio.h>

static int	choose_arg(char det, va_list *ap)
{
	if (det == 'c')
		return (ft_print_char(va_arg(*ap, int)));
	else if (det == 's')
		return (ft_print_str(va_arg(*ap, char *)));
	else if (det == 'p')
		return (ft_print_pointer(va_arg(*ap, unsigned long)));
	else if (det == 'd')
		return (ft_print_int(va_arg(*ap, int)));
	else if (det == 'i')
		return (ft_print_int(va_arg(*ap, int)));
	else if (det == 'u')
		return (ft_print_uns_int(va_arg(*ap, unsigned int)));
	else if (det == 'x')
		return (ft_print_hex_low(va_arg(*ap, int)));
	else if (det == 'X')
		return (ft_print_hex_up(va_arg(*ap, int)));
	else if (det == '%')
		return (ft_print_char('%'));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	va_list	*pap;
	int		size;
	int		buff;
	size_t	cu;

	va_start(ap, s);
	pap = &ap;
	size = 0;
	buff = 0;
	cu = 0;
	if (!s)
		return (-1);
	while (s[cu])
	{
		if (s[cu] == '%')
		{
			buff = choose_arg(s[cu + 1], pap);
			if (buff == -1)
				return (0);
			size += buff;
			cu += 2;
		}
		else
		{
			write(1, &s[cu], 1);
			cu++;
			size++;
		}
	}
	va_end(ap);
	return (size);
}
/*
int	main()
{
	void	*p = malloc(12);

	int	f = ft_printf("%p\n", p);

	int	n = printf("%p\n", p);

	printf("ft : %i\nprintf : %i\n", f, n);
	return 0;
}*/
