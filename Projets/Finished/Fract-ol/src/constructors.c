/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:53:19 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/20 18:03:23 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Initialize mlx server and create a window 
// Returns a pointer to a struct containing pointers to mlx and window
t_mlx_data	*new_mlx_data(t_reso *s_reso, char *win_name)
{
	t_mlx_data	*s_mlx;

	s_mlx = malloc(sizeof(t_mlx_data));
	if (!s_mlx)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_mlx->mlx = mlx_init();
	if (!s_mlx->mlx)
	{
		free(s_mlx);
		return (NULL);
	}
	s_mlx->win = mlx_new_window(s_mlx->mlx, s_reso->x_reso, s_reso->y_reso,
			win_name);
	if (!s_mlx->win)
	{
		mlx_destroy_display(s_mlx->mlx);
		free(s_mlx);
		return (NULL);
	}
	return (s_mlx);
}

// Create an image and fill up its struct
// Returns a pointer to a struct containing initialized image and its resolution
t_img_data	*new_img_data(t_mlx_data *s_mlx, t_reso *s_reso)
{
	t_img_data	*s_img;

	s_img = malloc(sizeof(t_img_data));
	if (!s_img)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_img->img = mlx_new_image(s_mlx->mlx, s_reso->x_reso, s_reso->y_reso);
	if (!(s_img->img))
	{
		free(s_img);
		return (NULL);
	}
	s_img->addr = mlx_get_data_addr(s_img->img, &(s_img->bit_per_pixel),
			&(s_img->line_length), &(s_img->endian));
	if (!(s_img->addr))
	{
		mlx_destroy_image(s_mlx->mlx, s_img->img);
		free(s_img);
		return (NULL);
	}
	s_img->s_reso = s_reso;
	return (s_img);
}

// Returns a pointer to a struct containing infos about the fract to draw
// We adapt its frame for Mandel or Julia set according to the init point
t_fract	*new_fract(t_cpx_pt *s_init, t_reso *s_reso,
	int max_iter, t_color **grad)
{
	t_fract	*s_frc;

	if (!s_init || !grad || !s_reso)
		return (NULL);
	s_frc = malloc(sizeof(t_fract));
	if (!s_frc)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_frc->s_init = s_init;
	s_frc->gradient = grad;
	if (s_init->r == 0 && s_init->i == 0)
		s_frc->s_frame = new_frame(-3.15, 1.65, -1.2, 1.2);
	else
		s_frc->s_frame = new_frame(-1, 1, -1.2, 1.2);
	if (!(s_frc->s_frame))
	{
		free(s_frc);
		return (NULL);
	}
	s_frc->max_iter = max_iter;
	s_frc->zoom_x = s_reso->x_reso / (s_frc->s_frame->x2 - s_frc->s_frame->x1);
	s_frc->zoom_y = s_reso->y_reso / (s_frc->s_frame->y2 - s_frc->s_frame->y1);
	return (s_frc);
}

// Returns a pointer to a struct containing all the data needed to draw and 
// print the fractal
t_global	*new_global(t_cpx_pt *s_init, t_reso *s_reso,
	int max_iter, t_color **grad)
{
	t_global	*s_glb;

	if (!s_init || !s_reso || !grad)
		return (NULL);
	s_glb = malloc(sizeof(t_global));
	if (!s_glb)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_glb->s_mlx = new_mlx_data(s_reso, "Fract-ol");
	if (!(s_glb->s_mlx))
		free_global_ex(s_glb, EXIT_FAILURE);
	s_glb->s_img = new_img_data(s_glb->s_mlx, s_reso);
	if (!(s_glb->s_img))
		free_global_ex(s_glb, EXIT_FAILURE);
	s_glb->s_fract = new_fract(s_init, s_reso, max_iter, grad);
	if (!(s_glb->s_fract))
		free_global_ex(s_glb, EXIT_FAILURE);
	return (s_glb);
}

// Returns a pointer to a struct containing boundaries of the complex plan
t_frame	*new_frame(double x1, double x2, double y1, double y2)
{
	t_frame	*s_frame;

	s_frame = malloc(sizeof(t_frame));
	if (!s_frame)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_frame->x1 = x1;
	s_frame->x2 = x2;
	s_frame->y1 = y1;
	s_frame->y2 = y2;
	return (s_frame);
}
