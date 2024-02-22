/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:02:04 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 11:23:39 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Renvoie un int correspondant a une couleur interpretable pour mlx 
// Pas sur que la fonction soit necessaire y en a une fournie dans mlx
int	create_trgb(int t, int r, int g, int b)
{
	if(t > 256 | r > 256 | g > 256 | b > 256)
		return (0);
	return (t << 24 | r << 16 | g << 8 | b);
}

// Fonction plus performante que mlx_pixel_put
// Dessine un pixel sur une image en changeant directement dans la zone memoire
// Fait fi du "offset" ??? a checker
void	put_pixel_to_image(t_img_data *s_img, int x, int y, int color)
{
	char	*dst;
	
	dst = s_img->addr + (x * (s_img->bit_per_pixel/8) + y * s_img->line_length);
	*(unsigned int *)dst = color;
}

int	get_color_gradient(int iter, int max_iter, long *gradient)
{
	int	color;
	
	if (iter == max_iter)
		return (0);
	color = gradient [(10 * iter / max_iter)];
	
	return (color);
}

// int	*create_gradient(int grad_length)
// {
// 	int		*grad;
// 	int		i;
// 	int		base;
	
// 	grad = malloc((grad_length + 1) * sizeof(int));
// 	if (!grad)
// 		return (NULL);
// 	i = 0;
// 	base = create_trgb(256, 0, 0, 256);
// 	while (i <= grad_length)
// 	{
// 		grad[i] = create_trgb(256, i * 256 / grad_length, 0, 256 - i *0.9);
// 		i++;
// 	}
// 	return (grad);
// }

int	*create_gradient(int grad_length)
{
	int	*grad;
	int	i;
	
	grad = malloc((grad_length + 1) * sizeof(int));
	if (!grad)
		return (NULL);	
	grad[grad_length - 1] = create_trgb(0, 0, 0, 0);
	i = 0;
	while (i < grad_length - 1)
	{
	grad[i] = create_trgb(256, 150 / (1+i*2.5), 0, 256 * i / grad_length);
		// if (i < grad_length / 3)
		// 	grad[i] = create_trgb(255, 0, 0, 255 - i * 3);	
		// else if (i >= grad_length / 3 && i < 2 * grad_length / 3)
		// 	grad[i] = create_trgb(255, 255 - i * 3, 0, 0);
		// else
		// 	grad[i] = create_trgb(255, 0, 255 - i * 3, 0);
		i++;
	}
	return (grad);
}
long	*load_gradient(int fd, int grad_length)
{
	long	*grad;
	int	i;
	char	*buff;	
	grad = malloc(sizeof(long) * (grad_length + 1));
	if (!grad)
		return (NULL);
	i = 0;
	while (i < grad_length)
	{
		buff = get_next_line(fd);
		grad[i] = ft_atol(buff);
		// grad[i] = fd;
		i++;
	}
	return (grad);
}
// Gere les arguments en entree et les check
int	menu (int ac, char *av[])
{
	if (ac < 2)
	{
		ft_putstr("This program takes at leat 2 arguments !\nTry ./fractol m or ./fractol j\n");
		exit(1);
	}
	else if (!ft_isalpha(av[1][0]) || (av[1][0] != 'm' && av[1][0] != 'j'))
	{
		ft_putstr("This program only takes \"m\" (for Mandelbrot set) or \"j\" (for Julia set) as first parameter\n");
		exit(1);
	}
	else if (av[1][0] == 'j' && ac < 4)
	{
		ft_putstr("This program need a starting point for the Julia set\nTry ./fractol j 0.285 0.01\n");
		exit(1);
	}	
	else
		return (av[1][0]);
	return (0);
}