/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:33:03 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/16 17:21:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_collision(t_global *s_global, t_vec *next_pos)
{
	unsigned long	next_x;
	unsigned long	next_y;

	next_x = floor(next_pos->x);
	next_y = floor(next_pos->y);
	if (!(s_global->s_map->map_tab[next_y][next_x]))
		return (true);
	if (!is_player_spawn(s_global->s_map->map_tab[next_y][next_x])
		&& s_global->s_map->map_tab[next_y][next_x] != '0')
		return (true);
	return (false);
}

void	rotate_p_dir(t_raycast *s_raycast, int keycode, double angle)
{
	t_vec	tmp_player;
	t_vec	tmp_plane;

	if (keycode == LEFT_ARROW)
		angle = -angle;
	tmp_player.x = s_raycast->p_dir.x;
	tmp_player.y = s_raycast->p_dir.y;
	s_raycast->p_dir.x = tmp_player.x * cos(angle) - tmp_player.y * sin(angle);
	s_raycast->p_dir.y = tmp_player.x * sin(angle) + tmp_player.y * cos(angle);
	tmp_plane.x = s_raycast->plane.x;
	tmp_plane.y = s_raycast->plane.y;
	s_raycast->plane.x = tmp_plane.x * cos(angle) - tmp_plane.y * sin(angle);
	s_raycast->plane.y = tmp_plane.x * sin(angle) + tmp_plane.y * cos(angle);
}

static void	move_player_right(t_vec *tmp, t_raycast *s_raycast, double distance)
{
	tmp->x = s_raycast->p_pos.x - s_raycast->p_dir.y * distance;
	tmp->y = s_raycast->p_pos.y + s_raycast->p_dir.x * distance;
}

bool	move_player(t_global *s_global, t_raycast *s_raycast, int keycode,
		double distance)
{
	t_vec	tmp;

	tmp.x = 0;
	if (keycode == W_KEY)
	{
		tmp.x = s_raycast->p_pos.x + s_raycast->p_dir.x * distance;
		tmp.y = s_raycast->p_pos.y + s_raycast->p_dir.y * distance;
	}
	else if (keycode == S_KEY)
	{
		tmp.x = s_raycast->p_pos.x - s_raycast->p_dir.x * distance;
		tmp.y = s_raycast->p_pos.y - s_raycast->p_dir.y * distance;
	}
	else if (keycode == A_KEY)
	{
		tmp.x = s_raycast->p_pos.x + s_raycast->p_dir.y * distance;
		tmp.y = s_raycast->p_pos.y - s_raycast->p_dir.x * distance;
	}
	else if (keycode == D_KEY)
		move_player_right(&tmp, s_raycast, distance);
	if (check_collision(s_global, &tmp))
		return (false);
	s_raycast->p_pos.x = tmp.x;
	s_raycast->p_pos.y = tmp.y;
	return (true);
}
