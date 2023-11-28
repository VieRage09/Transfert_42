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

int	ft_print_uns_int(unsigned int u)
{
	char	*s;

	s = ft_itoa(u);
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}
