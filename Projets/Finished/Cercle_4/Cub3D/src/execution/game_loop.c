/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:35:08 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 18:08:45 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cross_hook(t_global *s_global)
{
	free_global_exit(s_global, EXIT_SUCCESS);
	return (0);
}

int	handle_keyhook(int keycode, t_global *s_global)
{
	if (keycode == ESCAPE)
		free_global_exit(s_global, EXIT_SUCCESS);
	if (keycode == W_KEY || keycode == S_KEY
		|| keycode == A_KEY || keycode == D_KEY)
	{
		move_player(s_global, s_global->s_raycast, keycode, 0.2);
		draw_frame(s_global);
	}
	if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
	{
		rotate_p_dir((s_global->s_raycast), keycode, 0.2);
		draw_frame(s_global);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_global *s_global)
{
	x = 0;
	y = 0 + x;
	x = 0 + y;
	if (button == 1)
	{
		rotate_p_dir((s_global->s_raycast), LEFT_ARROW, 0.2);
		draw_frame(s_global);
	}
	else if (button == 3)
	{
		rotate_p_dir((s_global->s_raycast), RIGHT_ARROW, 0.2);
		draw_frame(s_global);
	}
	else
		ft_printf("button pressed = %i\n", button);
	return (0);
}

void	game_loop(t_global *s_global)
{
	ft_printf("Drawing frame\n");
	draw_frame(s_global);
	mlx_hook(s_global->s_mlx->mlx_win, 17, 0, cross_hook, s_global);
	mlx_hook(s_global->s_mlx->mlx_win, 2, 1L << 0, handle_keyhook, s_global);
	mlx_hook(s_global->s_mlx->mlx_win, 4, 1L << 2, mouse_hook, s_global);
	mlx_loop(s_global->s_mlx->mlx);
}
