/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:01:35 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/28 18:17:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libftprintf.h"
#include"libft/libft.h"

int	ft_print_int(int n)
{
	char	*s;
	
	s = ft_itoa(n);
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}
