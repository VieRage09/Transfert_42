/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:07:00 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/28 19:10:01 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft/libft.h"

/*static int	ucount_digit(unsigned int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_uitoa(unsigned int u)
{
	char	*s;
	int	digits;

	digits = ucount_digit(u);
	s = malloc((digits + 1) * sizeof(char));
	if(!s)
		return(NULL);
	s[digits] = '\0';
	digits -= 1;
	while (digits >= 0)
	{
		s[digits] = u % 10;
		u /= 10;
		digits--;	
	}
	return (s);
}
*/
int	ft_print_uns_int(unsigned int u)
{
	char	*s;
	int	size;

	s = ft_itoa(u);
	if (!s)
		return (-1);
	size = ft_strlen(s);
	write(1, s, size);
	free(s);
	return (size);
}
