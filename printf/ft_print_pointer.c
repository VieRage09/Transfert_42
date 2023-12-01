/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:04:55 by tlebon            #+#    #+#             */
/*   Updated: 2023/11/28 19:16:15 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_print_pointer(void *p)
{
	
	write(1,p, 8);	
	return (0);
}

/*static char	*ft_longtohexa(void *p)
{
	char	*s;

	s = malloc(14); // Taille de n importe quelle adresse en hexa ???
	if (!s)
		return (NULL);
	
	return s;	



}*/
