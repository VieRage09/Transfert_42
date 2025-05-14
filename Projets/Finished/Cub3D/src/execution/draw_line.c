/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:59:23 by lberne            #+#    #+#             */
/*   Updated: 2025/04/08 18:28:38 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	harvest_ceilfloor_colors(t_global *s_global, int pickme)
{
	char	*tmp;
	char	*str;
	int		r;
	int		g;
	int		b;

	str = NULL;
	r = 0;
	g = 0;
	b = 0;
	if (pickme == 0)
		str = ft_strdup(s_global->s_map->s_texture.ceiling);
	else if (pickme == 1)
		str = ft_strdup(s_global->s_map->s_texture.floor);
	if (!str)
		return (-1);
	r = ft_atoi(str);
	tmp = ft_strchr(str, ',');
	g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	b = ft_atoi(tmp + 1);
	free(str);
	return (create_trgb(255, r, g, b));
}

int	t_index(t_raycast *raycast)
{
	int	texture_index;

	if (raycast->side == 1)
	{
		if (raycast->raydir.y < 0)
			texture_index = 0;
		else
			texture_index = 1;
	}
	else
	{
		if (raycast->raydir.x > 0)
			texture_index = 2;
		else
			texture_index = 3;
	}
	return (texture_index);
}

void	init_draw_data(t_draw *draw, t_raycast *raycast, t_global *s_global)
{
	draw->tex_id = t_index(raycast);
	draw->line_height = HEIGHT * (1 / raycast->w_dist);
	draw->draw_start = (HEIGHT / 2) - (draw->line_height / 2);
	draw->draw_end = (HEIGHT / 2) + (draw->line_height / 2);
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	if (raycast->side == 0)
		draw->wall_x = raycast->p_pos.y + raycast->w_dist * raycast->raydir.y;
	else
		draw->wall_x = raycast->p_pos.x + raycast->w_dist * raycast->raydir.x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x
			* (double)s_global->tex[draw->tex_id].width);
	if (raycast->side == 0 && raycast->raydir.x > 0)
		draw->tex_x = s_global->tex[draw->tex_id].width - draw->tex_x - 1;
	if (raycast->side == 1 && raycast->raydir.y < 0)
		draw->tex_x = s_global->tex[draw->tex_id].width - draw->tex_x - 1;
	draw->step = 1.0 * s_global->tex[draw->tex_id].height / draw->line_height;
	draw->tex_pos = (draw->draw_start - HEIGHT / 2 + draw->line_height / 2)
		* draw->step;
	draw->ceilling = harvest_ceilfloor_colors(s_global, 0);
	draw->floor = harvest_ceilfloor_colors(s_global, 1);
}

void	draw_vertical_line(t_img_data *data, int x, t_global *s_global)
{
	t_raycast	*raycast;
	t_draw		draw;
	int			i;
	int			y;

	raycast = s_global->s_raycast;
	init_draw_data(&draw, raycast, s_global);
	i = 0;
	while (i++ < draw.draw_start)
		my_mlx_pixel_put(data, x, i, draw.ceilling);
	y = draw.draw_start;
	while (y++ < draw.draw_end)
	{
		draw.tex_y = (int)draw.tex_pos
			& (s_global->tex[draw.tex_id].height - 1);
		draw.tex_pos += draw.step;
		draw.color = *(int *)(s_global->tex[draw.tex_id].addr
				+ (draw.tex_y * s_global->tex[draw.tex_id].line_length
					+ draw.tex_x
					* (s_global->tex[draw.tex_id].bits_per_pixel / 8)));
		my_mlx_pixel_put(data, x, y, draw.color);
	}
	i = draw.draw_end;
	while (i++ < HEIGHT - 1)
		my_mlx_pixel_put(data, x, i, draw.floor);
}
