/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:34:00 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/08 13:12:33 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// For the norme : used by update_s_raycast to finish init
static void	update_s_raycast_end(t_raycast *s_raycast)
{
	if (s_raycast->raydir.x < 0)
	{
		s_raycast->step.xpos = -1;
		s_raycast->side_dist.x = (s_raycast->p_pos.x
				- s_raycast->p_map.xpos) * s_raycast->delta_dist.x;
	}
	else
	{
		s_raycast->step.xpos = 1;
		s_raycast->side_dist.x = (s_raycast->p_map.xpos + 1.0
				- s_raycast->p_pos.x) * s_raycast->delta_dist.x;
	}
	if (s_raycast->raydir.y < 0)
	{
		s_raycast->step.ypos = -1;
		s_raycast->side_dist.y = (s_raycast->p_pos.y
				- s_raycast->p_map.ypos) * s_raycast->delta_dist.y;
	}
	else
	{
		s_raycast->step.ypos = 1;
		s_raycast->side_dist.y = (s_raycast->p_map.ypos + 1.0
				- s_raycast->p_pos.y) * s_raycast->delta_dist.y;
	}
}

// Used at each vertical stripe to init properly the struct with right values
static void	update_s_raycast(t_raycast *s_raycast, int x)
{
	s_raycast->hit = 0;
	s_raycast->raydir.x = (2 * x / (double)WIDTH - 1)
		* s_raycast->plane.x + s_raycast->p_dir.x;
	s_raycast->raydir.y = (2 * x / (double)WIDTH - 1)
		* s_raycast->plane.y + s_raycast->p_dir.y;
	s_raycast->p_map.xpos = (int)(s_raycast->p_pos.x);
	s_raycast->p_map.ypos = (int)(s_raycast->p_pos.y);
	if (s_raycast->raydir.x == 0)
		s_raycast->delta_dist.x = 1e30;
	else
		s_raycast->delta_dist.x = fabs(1 / s_raycast->raydir.x);
	if (s_raycast->raydir.y == 0)
		s_raycast->delta_dist.y = 1e30;
	else
		s_raycast->delta_dist.y = fabs(1 / s_raycast->raydir.y);
	update_s_raycast_end(s_raycast);
}

// Raycasting a proprement parler
static void	raycharles_algo(t_global *s_global, t_raycast *s_raycast)
{
	while (s_raycast->hit == 0)
	{
		if (s_raycast->side_dist.x < s_raycast->side_dist.y)
		{
			s_raycast->side_dist.x += s_raycast->delta_dist.x;
			s_raycast->p_map.xpos += s_raycast->step.xpos;
			s_raycast->side = 0;
		}
		else
		{
			s_raycast->side_dist.y += s_raycast->delta_dist.y;
			s_raycast->p_map.ypos += s_raycast->step.ypos;
			s_raycast->side = 1;
		}
		if (s_global->s_map->map_tab[s_raycast->p_map.ypos]
			[s_raycast->p_map.xpos] == '1')
			s_raycast->hit = 1;
	}
}

// Creates a new image and iterates through all vertical stripes of the window
// and perform DDA then calculates wall distance and prints the vertical line
void	draw_frame(t_global *s_global)
{
	t_img_data	img;
	t_raycast	*s_raycast;
	int			x;

	s_raycast = s_global->s_raycast;
	x = 0;
	img.img = mlx_new_image(s_global->s_mlx->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	while (x < WIDTH)
	{
		update_s_raycast(s_raycast, x);
		raycharles_algo(s_global, s_raycast);
		if (s_raycast->side == 0)
			s_raycast->w_dist = s_raycast->side_dist.x
				- s_raycast->delta_dist.x;
		else
			s_raycast->w_dist = s_raycast->side_dist.y
				- s_raycast->delta_dist.y;
		draw_vertical_line(&img, x, s_global);
		x++;
	}
	mlx_put_image_to_window(s_global->s_mlx->mlx, s_global->s_mlx->mlx_win,
		img.img, 0, 0);
	mlx_destroy_image(s_global->s_mlx->mlx, img.img);
}
