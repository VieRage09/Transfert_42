/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/17 22:53:54 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Renvoie un int valant la couleur RGB
int	create_trgb(int t, int r, int g, int b)
{
	if(t > 256 | r > 256 | g > 256 | b > 256)
		return (0);
	return (t << 24 | r << 16 | g << 8 | b);
}
// Pour un point c(x;y) du plan complexe, calcule le nombre d'iteration necessaire a la suite Z(n+1) = Z(n)^2 + c pour que son module depasse 2 
// Aka Si la fonction suivante renvoie un nombre egale a max_iterations, le point c appartient a l'ensemble de Mandelbrot
int	calc_for_point(double x, double y, int max_iterations)
{
	int	iter;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	tmp;
	
	iter = 0;
	c_r = x;
	c_i = y;
	z_r = 0;
	z_i = 0;
	while ((z_r * z_r) + (z_i * z_i) < 4 && iter < max_iterations)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + c_r;
		z_i = (2 * tmp * z_i) + c_i;
		iter++;
	}
	return (iter);
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

int	draw_fract_on_img(t_img_data *s_img, int x_size, int y_size, int max_iterations)
{
	//Definit la plage du plan complex a afficher, attention peut rendre la
	//fractal disproportionnee --> Formule a trouver 
	double	x1 = -3.15;
	double	x2 = 1.65;
	double	y1 = -1.2;
	double	y2 = 1.2;
	// I guess defini le facteur d'agrandissement
	double	zoom_x = x_size/(x2 - x1);
	double	zoom_y = y_size/(y2 - y1);
	// Les coordonnes dans l'image
	int it;
	int	x = 0;
	while (x < x_size)
	{
		int	y = 0;
		while (y < y_size)
		{
			if ((it = calc_for_point((x / zoom_x) + x1, (y / zoom_y) + y1, max_iterations)) == max_iterations)
				put_pixel_to_image(s_img, x, y, 0x00000000);
			else if (it > 0)
				put_pixel_to_image(s_img, x, y, create_trgb(255, 0, 255*it / max_iterations * 2 , 255*it / max_iterations));
			else
				put_pixel_to_image(s_img, x, y, create_trgb(0, 0, 0 , 0));
			y++;
		}
		x++;
	}	

	return (0);
}
// int	draw_fract_on_img2(t_img_data *s_img, int max_iterations)
// {
// 	// xn definit la plage du plan complex a afficher
// 	float	x1 = -2.1;
// 	float	x2 = 0.6;
// 	float	y1 = -1.2;
// 	float	y2 = 1.2;
// 	int		zoom = 300;
// 	// I guess defini le facteur d'agrandissement
// 	float	x_size = (x2 - x1) * zoom;
// 	float	y_size = (y2 - y1) * zoom;
// 	// Les coordonnes dans l'image
// 	int	x = 0;
//		
// 	while (x < x_size)
// 	{
// 		int	y = 0;
// 		while (y < y_size)
// 		{
// 			if (calc_for_point((x / zoom) + x1, (y / zoom) + y1, max_iterations) == max_iterations)
// 				put_pixel_to_image(s_img, x, y, 0x00000000);
// 			else
// 				put_pixel_to_image(s_img, x, y, 0xFF4287F5);
// 			y++;
// 		}
// 		x++;
// 	}	
// 	return (0);
// }

// int	main()
int	main(int ac, char *av[])
{
	const int	X_RES = 1920;
	const int	Y_RES = 1080;
	// Gestion des mauvaises entrees
	if (ac < 2)
	{
		ft_putstr("\033[1;31mNot enough arguments\n\033[0mThe \033[1;32mcorrect\033[0m use is:\n./fractol m\n./fractol j <number>\n");
		return (1);
	}
	else if (av[1][0] == 'm')
		ft_putstr("Ensemble de Mandelbrot selectionne\n");
	////////////////////////////////
	t_mlx_data	s_mlx;
	t_img_data	s_img;
	
	// Initialiation of mlx and window
	s_mlx.mlx = mlx_init();
	if(!s_mlx.mlx)
		return (1);
	s_mlx.win = mlx_new_window(s_mlx.mlx, X_RES, Y_RES, "Fractol");
	if (!s_mlx.win)
		return (1);
	
	// Creation of an image
	s_img.img = mlx_new_image(s_mlx.mlx, X_RES, Y_RES);
	if(!s_img.img)
		return(1);
	s_img.addr = mlx_get_data_addr(s_img.img, &s_img.bit_per_pixel, 
									&s_img.line_length, &s_img.endian);
	////////////////////////
	draw_fract_on_img(&s_img, X_RES, Y_RES, ft_atoi(av[2]));
	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_img.img, 0, 0);
	mlx_loop(s_mlx.mlx);
	return (0);	
}

