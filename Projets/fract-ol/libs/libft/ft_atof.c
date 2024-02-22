/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 06:24:39 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 07:09:01 by tlebon           ###   ########.fr       */
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

float	ft_atof(const char *nptr)
{
	int		i;
	float	nbr;
	int		sign;
	int		point;

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
	i = ft_strlen(nptr) - 1;
	while ((ft_isdigit(nptr[i]) || nptr[i] == '.') && point <= 1 && i >= 0)
	{
		if (nptr[i] == '.')
			point++;
		else
			nbr = nbr / 10 + (nptr[i] - '0');
		i--;
	}
	return (sign * nbr);
}
