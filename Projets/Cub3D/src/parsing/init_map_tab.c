/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:10:28 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 19:02:08 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Skip then blank lines then go through all the map to get its size
// Also checks if there is a blank line inside the map definition
// Returns FALSE on error
static	bool	init_map_size(t_map *s_map, int fd)
{
	char	*line;

	line = free_strtrim(get_next_line(fd), "\n");
	while (line && ft_str_is_wspace(line))
	{
		free(line);
		line = free_strtrim(get_next_line(fd), "\n");
	}
	if (!line)
		return (false);
	s_map->height = 0;
	s_map->width = 0;
	while (line && !ft_is_blanckline(line))
	{
		if (ft_strlen(line) > s_map->width)
			s_map->width = ft_strlen(line);
		s_map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (ft_str_is_wspace(line))
		return (free(line), ft_putstr_fd("Blank line inside map\n", 2), false);
	return (true);
}

// Used on the second opening of the map file to skip the textures paths
static bool	skip_textures(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (false);
	while (line)
	{
		while (line && ft_str_is_wspace(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		count++;
		if (!line)
			return (false);
		free(line);
		if (count == 6)
			break ;
		line = get_next_line(fd);
	}
	return (true);
}

// Allocates and prepares the string that are going to map_tab accordingly
// --> No trailing spaces \n nor tabs
// Returns NULL on error
static char	*create_map_tab_str(char *line, size_t size)
{
	char	*str;
	char	*trim;
	size_t	i;

	trim = trim_trail(line);
	if (!trim)
		return (NULL);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (free(trim), NULL);
	i = 0;
	while (trim[i])
	{
		str[i] = trim[i];
		i++;
	}
	while (i < size - 1)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (free(trim), str);
}

// Allocates map tab accordingly then reads the map file to fill it up
// Return false on error
static bool	fill_map_tab(t_map *s_map, int fd)
{
	char	*line;
	size_t	i;

	s_map->map_tab = malloc((s_map->height + 1) * sizeof(char *));
	if (!s_map->map_tab)
		return (false);
	s_map->map_tab[s_map->height] = NULL;
	line = get_next_line(fd);
	while (line && ft_str_is_wspace(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (i < s_map->height)
	{
		s_map->map_tab[i] = create_map_tab_str(line, s_map->width);
		if (!s_map->map_tab[i])
			return (free(line), false);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (free(line), true);
}

// The reading head corresponding to fd is supposed to be positionned AFTER all
// textures path on the map file
// Reads the file until the end to calculate the size of the map then
// reopens the map file from the beginning to fill up map_tab of s_map
// Returns FALSE on error
bool	init_map_tab(t_map *s_map, char *path, int fd)
{
	if (!init_map_size(s_map, fd))
		return (close(fd), false);
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Open failed"), false);
	if (!skip_textures(fd))
		return (close(fd), false);
	if (!fill_map_tab(s_map, fd))
		return (close(fd), false);
	return (close(fd), true);
}
