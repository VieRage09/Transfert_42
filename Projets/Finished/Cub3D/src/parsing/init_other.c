/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:52:33 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 18:08:56 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_basic_vect(t_global *s_global, double x, double y)
{
	s_global->s_raycast->p_dir.x = x;
	s_global->s_raycast->p_dir.y = y;
	s_global->s_raycast->plane.x = -y;
	if (y == 0)
		s_global->s_raycast->plane.y = x;
	else
		s_global->s_raycast->plane.y = -x;
	if (s_global->s_raycast->plane.x > 0)
		s_global->s_raycast->plane.x -= FOV_VALUE;
	else if (s_global->s_raycast->plane.x < 0)
		s_global->s_raycast->plane.x += FOV_VALUE;
	else if (s_global->s_raycast->plane.y > 0)
		s_global->s_raycast->plane.y -= FOV_VALUE;
	else if (s_global->s_raycast->plane.y < 0)
		s_global->s_raycast->plane.y += FOV_VALUE;
}

bool	init_s_raycast(t_global *s_global)
{
	t_pos		spawn;

	find_player_spawn(s_global->s_map->map_tab, &spawn);
	s_global->s_raycast->p_pos.x = spawn.xpos + 0.5;
	s_global->s_raycast->p_pos.y = spawn.ypos + 0.5;
	if (s_global->s_map->map_tab[spawn.ypos][spawn.xpos] == 'N')
		init_basic_vect(s_global, 0, -1);
	if (s_global->s_map->map_tab[spawn.ypos][spawn.xpos] == 'S')
		init_basic_vect(s_global, 0, 1);
	if (s_global->s_map->map_tab[spawn.ypos][spawn.xpos] == 'W')
		init_basic_vect(s_global, -1, 0);
	if (s_global->s_map->map_tab[spawn.ypos][spawn.xpos] == 'E')
		init_basic_vect(s_global, 1, 0);
	return (true);
}

// Initialize mlx basics
// Returns false on error, true is the init is done properly
bool	init_s_mlx(t_mlx *s_mlx)
{
	s_mlx->mlx = mlx_init();
	if (!s_mlx->mlx)
		return (manage_error("Failed to init mlx\n"), false);
	s_mlx->mlx_win = mlx_new_window(s_mlx->mlx, WIDTH,
			HEIGHT, "cub3D");
	if (!s_mlx->mlx_win)
		return (manage_error("Failed to init mlx window\n"),
			mlx_destroy_display(s_mlx->mlx), false);
	return (true);
}

bool	load_xpm(t_global *s_global, int i)
{
	char	*path;

	if (i == 0)
		path = s_global->s_map->s_texture.no;
	if (i == 1)
		path = s_global->s_map->s_texture.so;
	if (i == 2)
		path = s_global->s_map->s_texture.ea;
	if (i == 3)
		path = s_global->s_map->s_texture.we;
	if (!is_xpm(path))
		return (ft_printf("%s : wrong format, please use .xpm\n", path), false);
	s_global->tex[i].img = mlx_xpm_file_to_image(s_global->s_mlx->mlx,
			path, &s_global->tex[i].width, &s_global->tex[i].height);
	if (!s_global->tex[i].img)
		return (false);
	s_global->tex[i].addr = mlx_get_data_addr(s_global->tex[i].img,
			&s_global->tex[i].bits_per_pixel,
			&s_global->tex[i].line_length, &s_global->tex[i].endian);
	return (true);
}

bool	load_textures(t_global *s_global)
{
	s_global->tex[0].img = NULL;
	s_global->tex[1].img = NULL;
	s_global->tex[2].img = NULL;
	s_global->tex[3].img = NULL;
	if (!load_xpm(s_global, 0))
		return (manage_error("Euh les textures la pas fou NO\n"), false);
	if (!load_xpm(s_global, 1))
		return (manage_error("Euh les textures la pas fou SO\n"), false);
	if (!load_xpm(s_global, 2))
		return (manage_error("Euh les textures la pas fou EA\n"), false);
	if (!load_xpm(s_global, 3))
		return (manage_error("Euh les textures la pas fou WE\n"), false);
	return (true);
}
