/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:53:19 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 07:15:39 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Initialize mlx server and create a window 
// Returns 0 on succes, 1 on error
int	mlx_data_constructor(t_mlx_data *s_mlx, t_reso *s_reso, char *win_name)
{
	s_mlx->mlx = mlx_init();
	if (!s_mlx->mlx)
		return (1);
	s_mlx->win = mlx_new_window(s_mlx->mlx, s_reso->x_reso, s_reso->y_reso,
			win_name);
	if (!s_mlx->win)
		return (1);
	return (0);
}

// Create an image and fill up its struct
// Returns 0 on succes, 1 on error
int	img_data_constructor(t_mlx_data *s_mlx, t_img_data *s_img, t_reso *s_reso)
{
	s_img->img = mlx_new_image(s_mlx->mlx, s_reso->x_reso, s_reso->y_reso);
	if (!s_img->img)
		return (1);
	s_img->addr = mlx_get_data_addr(s_img->img, &(s_img->bit_per_pixel),
			&(s_img->line_length), &(s_img->endian));
	s_img->x_reso = s_reso->x_reso;
	s_img->y_reso = s_reso->y_reso;
	return (0);
}
// void	set_cpx_pt_struct(t_cpx_pt *s_cpx_pt, double reel, double imaginary)
// {
// 	s_cpx_pt->r = reel;
// 	s_cpx_pt->i = imaginary;
// }

t_cpx_pt	*cpx_pt_constructor(double reel, double imaginary)
{
	t_cpx_pt	*s_cpx_pt;

	s_cpx_pt = malloc (sizeof(t_cpx_pt));
	if (!s_cpx_pt)
		return (NULL);
	s_cpx_pt->r = reel;
	s_cpx_pt->i = imaginary;
	return (s_cpx_pt);
}

void	set_frame_struct(t_frame *s_frame, char c, int x_size, int y_size)
{
	if (c == 'm')
	{
		s_frame->x1 = -3.15;
		s_frame->x2 = 1.65;
		s_frame->y1 = -1.2;
		s_frame->y2 = 1.2;
		s_frame->zoom_x = x_size / (s_frame->x2 - s_frame->x1);
		s_frame->zoom_y = y_size / (s_frame->y2 - s_frame->y1);
	}
	else if (c == 'j')
	{
		s_frame->x1 = -1;
		s_frame->x2 = 1;
		s_frame->y1 = -1.2;
		s_frame->y2 = 1.2;
		s_frame->zoom_x = x_size / (s_frame->x2 - s_frame->x1);
		s_frame->zoom_y = y_size / (s_frame->y2 - s_frame->y1);
	}
}

void	set_reso_struct(t_reso *s_reso, int x_reso, int y_reso)
{
	s_reso->x_reso = x_reso;
	s_reso->y_reso = y_reso;
}
