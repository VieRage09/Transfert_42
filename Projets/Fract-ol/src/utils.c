/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 22:26:32 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 22:02:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Handles prog inputs and checks them
void	menu(int ac, char *av[])
{
	if (ac < 3 || (av[1][0] != 'm' && av[1][0] != 'j') || ft_atoi(av[2]) < 1)
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
	return ;
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

// Opens the file corresponding to the value of key : from 1 to 6
// Returns the fd openned or -1 on error
int	open_grad(int key)
{
	int		fd;

	if (key == 1)
		fd = open("gradients/grad_1.txt", O_RDONLY);
	else if (key == 2)
		fd = open("gradients/grad_2.txt", O_RDONLY);
	else if (key == 3)
		fd = open("gradients/grad_3.txt", O_RDONLY);
	else if (key == 4)
		fd = open("gradients/grad_4.txt", O_RDONLY);
	else if (key == 5)
		fd = open("gradients/grad_5.txt", O_RDONLY);
	else if (key == 6)
		fd = open("gradients/grad_6.txt", O_RDONLY);
	else
		return (-1);
	if (fd < 0)
		perror("Open failed");
	return (fd);
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
