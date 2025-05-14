/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 01:39:44 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 22:09:29 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_player_spawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_valid(char c)
{
	if (c == '0' || c == '1' || is_player_spawn(c) || c == INSPACE || c == ' ')
		return (true);
	return (false);
}

bool	is_xpm(char *path)
{
	if (ft_strnstr(path, ".xpm", ft_strlen(path)) == NULL)
		return (false);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
		return (false);
	return (true);
}

bool	is_wspace(char c)
{
	if (!c)
		return (false);
	if (c <= 32 || c >= 127)
		return (true);
	else
		return (false);
}

void	print_map(t_map *s_map)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	copy = copy_map(s_map);
	while (copy[i])
	{
		j = 0;
		while (copy[i][j])
		{
			if (copy[i][j] == '0')
				copy[i][j] = '.';
			j++;
		}
		i++;
	}
	ft_print_str_tab(copy);
	ft_free_tab((void **)copy);
}
