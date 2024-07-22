/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:24:39 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 06:40:06 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atod(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;
	int	point;

	i = 0;
	nbr = 0;
	sign = 1;
	point = 0;
	while (ft_isspace(nptr[i]) || nptr[i] == '+' || nptr[i] == '-')
	{	
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while ((ft_isdigit(nptr[i]) || nptr[i] == '.') && point <= 1)
	{
		if (nptr[i] == '.')
			point++;
		else
			nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * nbr);
}
