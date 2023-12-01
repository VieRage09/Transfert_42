/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:11:47 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/28 19:18:10 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	choose_arg(char det, va_list *ap)
{
	if (det == 'c')
		return (ft_print_char(va_arg(*ap, int)));
	else if (det == 's')
		return (ft_print_str(va_arg(*ap, char *)));
	else if (det == 'p')
		return (ft_print_pointer(va_arg(*ap, void *)));
	else if (det == 'd')
		return (ft_print_int(va_arg(*ap, int)));
	else if (det == 'i')
		return (ft_print_int(va_arg(*ap, int)));
	else if (det == 'u')
		return (ft_print_uns_int(va_arg(*ap, unsigned int)));
	/*else if (det == 'x')
		return (print_hex_low(ap, ));
	else if (det == 'X')
		return (print_hex_up(ap, ));
	else if (det == '%')
		return (print_char('%');*/
	return (0);
}

int ft_printf(const char *s, ...)
{
	va_list	ap;
	va_list	*pap;
	int		size;
	size_t	cu;

	va_start(ap, s);
	pap = &ap;
	size = 0;
	cu = 0;
	if (!s)
		return (-1);
	while (s[cu])
	{
		if (s[cu] == '%')
		{
			// gerer le cas ou choosearg renvoie -1
			size += choose_arg(s[cu + 1], pap);
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
