/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:13:28 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 03:36:39 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Pour un point c(x;y) du plan complexe, calcule le nombre d'iteration necessaire a la suite Z(n+1) = Z(n)^2 + c pour que son module depasse 2 
// Aka Si la fonction suivante renvoie un nombre egale a max_iterations, le point c appartient a l'ensemble (de Mandelbrot si Z(0) = 0) (Julia si Z(0) = autre)
int	julman_pt_check(t_cpx_pt *s_init, double x, double y, int max_iter)
{
	int				iter;
	double			tmp;
	t_cpx_pt	s_c;
	t_cpx_pt s_z;
	
	iter = 0;
	s_c.r = x;
	s_c.i = y;
	s_z.r = s_init->r;
	s_z.i = s_init->i;
	while ((s_z.r * s_z.r) + (s_z.i * s_z.i) < 4 && iter < max_iter)
	{
		tmp = s_z.r;
		s_z.r = (s_z.r * s_z.r) - (s_z.i * s_z.i) + s_c.r;
		s_z.i = (2 * tmp * s_z.i) + s_c.i;
		iter++;
	}
	return (iter);
}

int	draw_julman(t_img_data *s_img, t_reso *s_reso, int max_iter)
{
	t_frame	s_frame;
	t_cpx_pt s_cpx_pt;
	int it;
	int	x;
	int	y;
		
	set_frame_struct(&s_frame, 'm', s_reso->x_reso, s_reso->y_reso);
	set_cpx_pt_struct(&s_cpx_pt, 0, 0);
	x = 0;
	while (x < s_reso->x_reso)
	{
		y = 0;
		while (y < s_reso->y_reso)
		{
			it = julman_pt_check(&s_cpx_pt, (x / s_frame.zoom_x) + s_frame.x1, (y / s_frame.zoom_y) + s_frame.y1, max_iter);
			if (it == max_iter)
				put_pixel_to_image(s_img, x, y, 0x00000000);
			else
				put_pixel_to_image(s_img, x, y, it);
			y++;
		}
		x++;
	}	
	return (0);
}


