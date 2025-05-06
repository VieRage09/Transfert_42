/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/08 07:13:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Euh pour l'instant mdr
void	manage_error(char *str_err)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str_err, 2);
}
