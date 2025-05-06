/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:50:23 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/17 17:44:46 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Supposed to free all the inside of s_map but not the struct
void	free_s_map(t_map *s_map)
{
	if (s_map->s_texture.no)
		free(s_map->s_texture.no);
	if (s_map->s_texture.so)
		free(s_map->s_texture.so);
	if (s_map->s_texture.ea)
		free(s_map->s_texture.ea);
	if (s_map->s_texture.we)
		free(s_map->s_texture.we);
	if (s_map->s_texture.floor)
		free(s_map->s_texture.floor);
	if (s_map->s_texture.ceiling)
		free(s_map->s_texture.ceiling);
	ft_free_tab((void **)s_map->map_tab);
	free(s_map);
}

void	destroy_texture(t_global *s_global)
{
	if ((s_global->tex)[0].img)
		mlx_destroy_image(s_global->s_mlx->mlx, (s_global->tex)[0].img);
	if ((s_global->tex)[1].img)
		mlx_destroy_image(s_global->s_mlx->mlx, (s_global->tex)[1].img);
	if ((s_global->tex)[2].img)
		mlx_destroy_image(s_global->s_mlx->mlx, (s_global->tex)[2].img);
	if ((s_global->tex)[3].img)
		mlx_destroy_image(s_global->s_mlx->mlx, (s_global->tex)[3].img);
}

void	free_s_mlx(t_global *s_global)
{
	mlx_destroy_window(s_global->s_mlx->mlx, s_global->s_mlx->mlx_win);
	mlx_destroy_display(s_global->s_mlx->mlx);
	free(s_global->s_mlx->mlx);
	free(s_global->s_mlx);
}

void	free_global(t_global *s_global)
{
	free_s_map(s_global->s_map);
	free(s_global->s_raycast);
	destroy_texture(s_global);
	free_s_mlx(s_global);
}

void	free_global_exit(t_global *s_global, int exit_status)
{
	free_global(s_global);
	exit(exit_status);
}
