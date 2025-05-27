/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:47:55 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 20:04:57 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_blanckline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

// Trims str of all char belonging to charset
// Frees the string in input(if str exists) and returns the trimmed one
char	*free_strtrim(char *str, char *charset)
{
	char	*trim;

	trim = ft_strtrim(str, charset);
	if (str)
		free(str);
	return (trim);
}

// Returns a copy of str trimmed of all trailing \n \t and spaces
// Returns NULL on error
char	*trim_trail(char *str)
{
	char	*trim;
	int		i;

	i = ft_strlen(str) - 1;
	if (i < 0)
		return (NULL);
	while (i > 0)
	{
		if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
			break ;
		i--;
	}
	trim = ft_substr(str, 0, i + 1);
	if (!trim)
		return (NULL);
	return (trim);
}

// Iterates through map to find the player spawn and update s_pos value
// Returns TRUE if only one player spawned is found
// False if there are more than one or if there is no spawn
bool	find_player_spawn(char **map, t_pos *s_pos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_spawn(map[i][j]))
			{
				s_pos->xpos = j;
				s_pos->ypos = i;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count == 1)
		return (true);
	return (false);
}

// Returns a copy of map_tab member of s_map
char	**copy_map(t_map *s_map)
{
	char	**copy;
	size_t	i;
	size_t	j;

	copy = malloc((s_map->height + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[s_map->height] = NULL;
	i = 0;
	while (s_map->map_tab[i])
	{
		copy[i] = malloc((s_map->width + 1) * sizeof(char));
		if (!copy[i])
			return (ft_free_tab((void **) copy), NULL);
		j = 0;
		while (j < s_map->width + 1)
		{
			copy[i][j] = s_map->map_tab[i][j];
			j++;
		}
		i++;
	}
	return (copy);
}
