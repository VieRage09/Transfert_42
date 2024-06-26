/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:42:32 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/22 16:11:48 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static char	*handle_min_int(char *str)
{
	str = malloc(12);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, "-2147483648", 12);
	return (str);
}

static int	count_digit(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= (-1);
		count++;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		sign_shift;

	str = NULL;
	sign_shift = 0;
	if (n == -2147483648)
		return (handle_min_int(str));
	digits = count_digit(n);
	str = malloc((digits + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= (-1);
		sign_shift = 1;
	}
	str[digits] = '\0';
	while (digits-- > 0 + sign_shift)
	{
		str[digits] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
