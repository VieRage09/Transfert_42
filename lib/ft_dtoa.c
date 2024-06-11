/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:54:10 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/11 20:45:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

// SUBOPTIMAL : Pas precis + gere uniquement une partie entier < MAX_INT
// et une partie fractionnaire < MAX_INT
// Takes a double and converts it to a string with decimals number precision
// Returns NULL on error
char	*ft_dtoa(double d, int decimals)
{
	char	*strint;
	char	*strfloat;
	char	*res;
	int		intpart;
	double	floatpart;

	intpart = (int) d;
	floatpart = d - (double)intpart;
	res = ft_itoa(intpart);
	if (!res)
		return (NULL);
	while (decimals-- > 0)
		floatpart *= 10;
	strfloat = ft_itoa((int)floatpart);
	if (!strfloat)
	{
		free(res);
		return (NULL);
	}
	strint = ft_strjoin(res, ".");
	free(res);
	res = ft_strjoin(strint, strfloat);
	free(strint);
	free(strfloat);
	return (res);
}
