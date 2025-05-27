/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 22:26:32 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/14 17:36:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Handles prog inputs and checks them
void	menu(int ac, char *av[])
{
	long	max_iter;

	if (ac < 3 || (av[1][0] != 'm' && av[1][0] != 'j') || ft_strlen(av[2]) > 11)
	{
		ft_putstr("Usage : ./fractol <p> <x>\n-> p as :\n	m (for Mandelbrot \
set)\n	j (for Julia set)\n-> x as an int > 0\n\n PS : for the julia set, you \
need to add the coordinates of the starting point as floating values\n");
		exit(1);
	}
	else if (av[1][0] == 'j' && ac < 5)
	{
		ft_putstr("You need to add a starting point for the Julia set\n\
Try ./fractol j 150 0.285 0.01\n");
		exit(1);
	}
	max_iter = ft_atol(av[2]);
	if (max_iter < 1 || max_iter > INT_MAX)
	{
		ft_putstr("x must be an INT > 0\n");
		exit(1);
	}
}

// Returns an int corresponding to rgb values but interpretable for mlx 
int	create_trgb(int t, int r, int g, int b)
{
	if ((t > 255) | (r > 255) | (g > 255) | (b > 255))
		return (0);
	return (t << 24 | r << 16 | g << 8 | b);
}

/////////////////////////// Fait fi du "offset" ??? a checker
// More efficient function than mlx_pixel_put present in mlx
// Draws on an image by writting directly to the memory
void	put_pixel_to_image(t_img_data *s_img, int x, int y, int color)
{
	char	*dst;

	dst = s_img->addr + (x * s_img->bit_per_pixel / 8 + y * s_img->line_length);
	*(unsigned int *)dst = color;
}

// Uses get_next_line to read a gradient file
// Returns a color struct corresponding to the gradient
// Returns NULL on error
t_color	*load_color(int fd)
{
	char	*line;
	int		r;
	int		g;
	int		b;

	line = get_next_line(fd);
	r = ft_atoi(line);
	free(line);
	line = get_next_line(fd);
	g = ft_atoi(line);
	free(line);
	line = get_next_line(fd);
	b = ft_atoi(line);
	free(line);
	line = get_next_line(fd);
	if (line[0] != '#')
	{
		free(line);
		return (NULL);
	}
	free(line);
	if (r == 0 && g == 0 && b == 0)
		return (NULL);
	return (new_color(r, g, b));
}

// Same process as ft_strjoin but frees the first string before returning
char	*str_append(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	return (res);
}
