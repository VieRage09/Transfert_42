/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 21:49:02 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Returns true if the file pointed to by path has the matching extension
static bool	check_extension(char *path, char *extension)
{
	size_t	p_size;
	size_t	e_size;
	char	*ext_comp;

	if (!path || !extension)
		return (false);
	p_size = ft_strlen(path);
	e_size = ft_strlen(extension);
	ext_comp = ft_substr(path, p_size - e_size, e_size);
	if (!ext_comp || ft_strncmp(extension, ext_comp, e_size) == 0)
		return (free(ext_comp), true);
	return (free(ext_comp), false);
}

// Initialize the global struct that contains all the necessary structs
// Returns false on error
bool	init_global(t_global *s_global, char *path)
{
	s_global->s_map = malloc(sizeof(t_map));
	if (!s_global->s_map)
		return (false);
	s_global->s_mlx = malloc(sizeof(t_mlx));
	if (!s_global->s_mlx)
		return (free(s_global->s_map), free(s_global), false);
	s_global->s_raycast = malloc(sizeof(t_raycast));
	if (!s_global->s_raycast)
		return (free(s_global->s_map), free(s_global->s_mlx), false);
	if (init_s_map(s_global->s_map, path) == false)
		return (free_s_map(s_global->s_map), free(s_global->s_mlx),
			free(s_global->s_raycast), false);
	if (init_s_mlx(s_global->s_mlx) == false)
		return (free_s_map(s_global->s_map), free(s_global->s_mlx),
			free(s_global->s_raycast), false);
	if (!load_textures(s_global))
		return (free_s_map(s_global->s_map), destroy_texture(s_global),
			free_s_mlx(s_global), free(s_global->s_raycast), false);
	if (init_s_raycast(s_global) == false)
		return (free_global(s_global), false);
	return (true);
}

int	main(int ac, char **av)
{
	t_global	s_global;

	if (ac != 2)
		return (ft_printf("Usage : ./cub3D valid_map_path\nThanks\n"), 1);
	if (check_extension(av[1], ".cub") == false)
		return (manage_error("You need to select a .cub file\n"), 2);
	if (!init_global(&s_global, av[1]))
		return (manage_error("Failed to init global_struct\n"), 3);
	ft_printf("Initialization success !\n Size of map = (%i ; %i)\n\n",
		s_global.s_map->width, s_global.s_map->height);
	game_loop(&s_global);
	return (0);
}
