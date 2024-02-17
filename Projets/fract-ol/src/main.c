/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/17 18:41:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	calc_for_point(float x, float y, int max_iterations)
{
	int	iter;
	float	c_r;
	float	c_i;
	float	z_r;
	float	z_i;
	float	tmp;
	
	iter = 0;
	c_r = x;
	c_i = y;
	z_r = 0;
	z_i = 0;
	while (z_r * z_r + z_i * z_i < 4 && iter < max_iterations)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_r * z_i + c_i;
		iter++;
	}
	return (iter);
}

int	main(int ac, char *av[])
{
	// Gestion des mauvaises entrees
	if (ac < 2)
	{
		ft_putstr("\033[1;31mNot enough arguments\n\033[0mThe \033[1;32mcorrect\033[0m use is:\n./fractol mandelbrot\n./fractol julia <number>\n");
		return (1);
	}
	////////////////////////////////
	t_mlx_data	s_mlx;
	t_img_data	s_img;
	
	// Initialiation of mlx and window
	s_mlx.mlx = mlx_init();
	if(!s_mlx.mlx)
		return (1);
	s_mlx.win = mlx_new_window(s_mlx.mlx, 1920, 1080, "Fractol");
	if (!s_mlx.win)
		return (1);
	
	// Creation of an image
	s_img.img = mlx_new_image(s_mlx.mlx, 1920, 1080);
	if(!s_img.img)
		return(1);
	s_img.addr = mlx_get_data_addr(s_img.img, &s_img.bit_per_pixel, 
									&s_img.line_length, &s_img.endian);
	mlx_pixel_put(s_mlx.mlx, s_mlx.win, 960, 540 , 0xFFFF0000);
	mlx_loop(s_mlx.mlx);

	return (0);	
}

