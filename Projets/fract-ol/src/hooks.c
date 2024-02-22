/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:32:50 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 00:33:32 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	escape_keyhook(int keycode, t_mlx_data *s_mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(s_mlx->mlx, s_mlx->win);
		exit(0);
	}
	return (1);
}

int	cross_button_hook(t_mlx_data *s_mlx)
{
	mlx_destroy_window(s_mlx->mlx, s_mlx->win);
	exit(0);
}