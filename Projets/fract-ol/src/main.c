/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 11:24:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	main(int ac, char *av[])
{
	const int	X_RES = 1920;
	const int	Y_RES = 1024;
	// const int	max_iter = ft_atoi(av[2]);
	const int	max_iter = 50;
	t_reso		s_reso;
	t_mlx_data	s_mlx;
	t_img_data	s_img;
	char		fract_type;
	long			*gradient;
	
	fract_type = menu(ac, av);
	int	fd;
	fd = open("/home/tlebon/Desktop/Transfert/Projets/fract-ol/colors/first", O_RDONLY);
	gradient = load_gradient(fd, 11);
	if (!gradient)
		return (1);
	set_reso_struct(&s_reso, X_RES, Y_RES);
	// Gestion des entrees de l'exec
	// Initialiation of mlx and window
	if(mlx_data_constructor(&s_mlx, &s_reso, "Fractol") != 0)
		return (1);
		
	// Creation of an image
	if (img_data_constructor(&s_mlx, &s_img, &s_reso) != 0)
		return (1);
	
	// Debut du programme 
	if (fract_type == 'm')
		draw_julman(&s_img, max_iter, cpx_pt_constructor(0, 0), gradient);
	else if (fract_type == 'j')
		draw_julman(&s_img, max_iter, cpx_pt_constructor(ft_atof(av[2]), ft_atof(av[3])), gradient);
	mlx_put_image_to_window(s_mlx.mlx, s_mlx.win, s_img.img, 0, 0);
	mlx_key_hook(s_mlx.win, escape_keyhook, &s_mlx);
	mlx_hook(s_mlx.win, 17, 1L<<5, cross_button_hook, &s_mlx); 
	mlx_loop(s_mlx.mlx);
	return (0);	
}

