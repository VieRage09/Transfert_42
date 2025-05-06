/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:03:55 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/16 20:06:27 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	la_norme_oh_que_oui(char*line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
	if (!ft_isdigit(line[*i]))
		return (false);
	while (ft_isdigit(line[*i]))
		(*i)++;
	while (ft_isspace(line[*i]))
	{
		(*i)++;
	}
	return (true);
}

static bool	check_rgb_line(char *line)
{
	int	i;

	i = 0;
	if (!la_norme_oh_que_oui(line, &i))
		return (false);
	if (line[i] != ',')
		return (false);
	i++;
	if (!la_norme_oh_que_oui(line, &i))
		return (false);
	if (line[i] != ',')
		return (false);
	i++;
	if (!la_norme_oh_que_oui(line, &i))
		return (false);
	if (line[i] != '\n' && line[i] != '\0')
		return (false);
	return (true);
}

bool	check_rgb(char *line)
{
	char	*tmp;
	char	*str;
	int		r;
	int		g;
	int		b;

	str = line + 1;
	if (!check_rgb_line(str))
		return (false);
	r = 0;
	g = 0;
	b = 0;
	r = ft_atoi(str);
	tmp = ft_strchr(str, ',');
	g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	b = ft_atoi(tmp + 1);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (false);
	return (true);
}
