/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:13:28 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 17:44:56 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Pour un point c(x;y) du plan complexe, calcule le nombre d'iteration
// necessaire a la suite Z(n+1) = Z(n)^2 + c pour que son module depasse 2 
// Aka Si la fonction suivante renvoie un nombre egale a max_iterations,
// le point c appartient a l'ensemble
// (Mandelbrot si Z(0) = 0) (Julia si Z(0) = autre)
int	man_pt_check(t_cpx_pt *s_init, double x, double y, int max_iter)
{
	int			iter;
	t_cpx_pt	s_c;
	t_cpx_pt	s_z;

	iter = 0;
	s_c.r = x;
	s_c.i = y;
	s_z.r = s_init->r;
	s_z.i = s_init->i;
	s_z.rxr = 0;
	s_z.ixi = 0;
	while ((s_z.rxr) + (s_z.ixi) < 4 && iter < max_iter)
	{
		s_z.i = 2 * s_z.r * s_z.i + s_c.i;
		s_z.r = s_z.rxr - s_z.ixi + s_c.r;
		s_z.rxr = s_z.r * s_z.r;
		s_z.ixi = s_z.i * s_z.i;
		++iter;
	}
	return (iter);
}

int	jul_pt_check(t_cpx_pt *s_init, double x, double y, int max_iter)
{
	int			iter;
	t_cpx_pt	s_c;
	t_cpx_pt	s_z;

	iter = 0;
	s_c.r = s_init->r;
	s_c.i = s_init->i;
	s_z.r = x;
	s_z.i = y;
	s_z.rxr = s_z.r * s_z.r;
	s_z.ixi = s_z.i * s_z.i;
	while ((s_z.rxr) + (s_z.ixi) < 4 && iter < max_iter)
	{
		s_z.i = 2 * s_z.r * s_z.i + s_c.i;
		s_z.r = s_z.rxr - s_z.ixi + s_c.r;
		s_z.rxr = s_z.r * s_z.r;
		s_z.ixi = s_z.i * s_z.i;
		++iter;
	}
	return (iter);
}

// Draws all pixels : for each processes how much iterations is needed 
// to tell that the pixel belongs or do not belongs to the fractal
// Depending on the iterations needed : puts a colored pixel to the image
int	draw_julman(t_img_data *s_img, t_fract *s_fract)
{
	int	iter;
	int	x;
	int	y;

	x = -1;
	while (++x < s_img->s_reso->x_reso)
	{
		y = -1;
		while (++y < s_img->s_reso->y_reso)
		{
			if (s_fract->s_init->r == 0 && s_fract->s_init->i == 0)
				iter = man_pt_check(s_fract->s_init, (x / s_fract->zoom_x)
						+ s_fract->s_frame->x1, (y / s_fract->zoom_y)
						+ s_fract->s_frame->y1, s_fract->max_iter);
			else
				iter = jul_pt_check(s_fract->s_init, (x / s_fract->zoom_x)
						+ s_fract->s_frame->x1, (y / s_fract->zoom_y)
						+ s_fract->s_frame->y1, s_fract->max_iter);
			put_pixel_to_image(s_img, x, y,
				get_color_grad(iter, s_fract->max_iter, s_fract->gradient,
					grad_size(s_fract->gradient)));
		}
	}	
	return (0);
}

// Creates a new image and draws onto it then put it on the window 
// Frees the original image 
int	refresh_img(t_global *s_glb)
{
	t_reso		*s_reso;
	t_img_data	*s_new_img;

	s_reso = s_glb->s_img->s_reso;
	s_new_img = new_img_data(s_glb->s_mlx, s_reso);
	draw_julman(s_new_img, s_glb->s_fract);
	mlx_destroy_image(s_glb->s_mlx->mlx, s_glb->s_img->img);
	free(s_glb->s_img);
	s_glb->s_img = s_new_img;
	if (!s_glb->s_img)
		return (1);
	mlx_put_image_to_window(s_glb->s_mlx->mlx, s_glb->s_mlx->win,
		s_glb->s_img->img, 0, 0);
	return (0);
}
