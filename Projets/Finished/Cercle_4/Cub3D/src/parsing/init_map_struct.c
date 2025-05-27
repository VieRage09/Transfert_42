/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:17:22 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 19:12:12 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	init_attr(char **attr, char *line, char *trim)
{
	char	*tmp;

	if (*attr)
		return (false);
	tmp = ft_substr(line, 2, ft_strlen(line));
	if (!tmp)
		return (false);
	*attr = ft_strtrim(tmp, trim);
	free(tmp);
	if (!attr)
		return (false);
	return (true);
}

// Used to assign each texture path to its correct member inside s_map
// Returns false on error or if the texture id isn't found
static bool	assign_correct_attribute(char *line, t_map *s_map)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "NO\t", 3) == 0)
		return (init_attr(&(s_map->s_texture.no), line, " \t\n"));
	else if (ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "SO\t", 3) == 0)
		return (init_attr(&(s_map->s_texture.so), line, " \t\n"));
	else if (ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "EA\t", 3) == 0)
		return (init_attr(&(s_map->s_texture.ea), line, " \t\n"));
	else if (ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "WE\t", 3) == 0)
		return (init_attr(&(s_map->s_texture.we), line, " \t\n"));
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "F\t", 2) == 0)
	{
		if (!check_rgb(line))
			return (manage_error("Wrong RGB definition\n"), false);
		return (init_attr(&(s_map->s_texture.floor), line, "F \t\n"));
	}
	else if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "C\t", 2) == 0)
	{
		if (!check_rgb(line))
			return (manage_error("Wrong RGB definition\n"), false);
		return (init_attr(&(s_map->s_texture.ceiling), line, "C \t\n"));
	}
	return (false);
}

// Goes through the map file until all the textures path are found
// Returns false on error or if there are missing textures
static bool	init_textures(t_map *s_map, int fd)
{
	int		count;
	char	*line;
	char	*trimed;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		while (line && ft_str_is_wspace(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		trimed = ft_strtrim(line, " \t");
		if (!trimed)
			return (free(line), false);
		if (!assign_correct_attribute(trimed, s_map))
			return (free(trimed), free(line), false);
		free(trimed);
		free(line);
		if (++count == 6)
			break ;
		line = get_next_line(fd);
	}
	return (count == 6);
}

// Opens the map file, then init every elements of s_map struct
// Returns false on error
bool	init_s_map(t_map *s_map, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	s_map->s_texture.no = NULL;
	s_map->s_texture.so = NULL;
	s_map->s_texture.ea = NULL;
	s_map->s_texture.we = NULL;
	s_map->s_texture.ceiling = NULL;
	s_map->s_texture.floor = NULL;
	s_map->map_tab = NULL;
	if (fd < 0)
		return (perror("Open failed"), false);
	if (!init_textures(s_map, fd))
		return (manage_error("Failed to init textures\n"), close(fd), false);
	if (!init_map_tab(s_map, path, fd))
		return (manage_error("Failed to init map tab\n"), false);
	if (!check_map(s_map))
		return (manage_error("Invalid Map\n"), false);
	return (true);
}
