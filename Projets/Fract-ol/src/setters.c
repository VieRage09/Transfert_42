/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:46:23 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 22:16:00 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Sets the s_reso struct to x and y
void	set_reso(t_reso *s_reso, int x_reso, int y_reso)
{
	s_reso->x_reso = x_reso;
	s_reso->y_reso = y_reso;
}

// Changes the frame through zoom factor 
void	set_frame_zoom(t_global *s_glb, double zoom, int x_pos, int y_pos)
{
	double	reel_x;
	double	reel_y;
	double	range_x;
	double	range_y;

	range_x = s_glb->s_fract->s_frame->x2 - s_glb->s_fract->s_frame->x1;
	range_y = s_glb->s_fract->s_frame->y2 - s_glb->s_fract->s_frame->y1;
	reel_x = (double)x_pos * range_x / s_glb->s_img->s_reso->x_reso
		+ s_glb->s_fract->s_frame->x1;
	reel_y = ((double)y_pos * range_y / s_glb->s_img->s_reso->y_reso
			+ s_glb->s_fract->s_frame->y1);
	s_glb->s_fract->s_frame->x1 = reel_x - (range_x / (zoom))
		* (double)x_pos / s_glb->s_img->s_reso->x_reso;
	s_glb->s_fract->s_frame->x2 = reel_x + (range_x / (zoom))
		* (1 - ((double)x_pos / s_glb->s_img->s_reso->x_reso));
	s_glb->s_fract->s_frame->y1 = reel_y - (range_y / (zoom))
		* (double)y_pos / s_glb->s_img->s_reso->y_reso;
	s_glb->s_fract->s_frame->y2 = reel_y + (range_y / (zoom))
		* (1 - ((double)y_pos / s_glb->s_img->s_reso->y_reso));
	s_glb->s_fract->zoom_x = s_glb->s_img->s_reso->x_reso
		/ (s_glb->s_fract->s_frame->x2 - s_glb->s_fract->s_frame->x1);
	s_glb->s_fract->zoom_y = s_glb->s_img->s_reso->y_reso
		/ (s_glb->s_fract->s_frame->y2 - s_glb->s_fract->s_frame->y1);
}

// Shifts the frame on the dir direction (north, south, east, west)
void	shift_frame(t_global *s_glb, char dir)
{
	double	range_x;
	double	range_y;

	range_x = s_glb->s_fract->s_frame->x2 - s_glb->s_fract->s_frame->x1;
	range_y = s_glb->s_fract->s_frame->y2 - s_glb->s_fract->s_frame->y1;
	if (dir == 'n')
	{
		s_glb->s_fract->s_frame->y1 -= range_y / 10;
		s_glb->s_fract->s_frame->y2 -= range_y / 10;
	}
	else if (dir == 's')
	{
		s_glb->s_fract->s_frame->y1 += range_y / 10;
		s_glb->s_fract->s_frame->y2 += range_y / 10;
	}
	else if (dir == 'e')
	{
		s_glb->s_fract->s_frame->x1 += range_x / 10;
		s_glb->s_fract->s_frame->x2 += range_x / 10;
	}
	else if (dir == 'w')
	{
		s_glb->s_fract->s_frame->x1 -= range_x / 10;
		s_glb->s_fract->s_frame->x2 -= range_x / 10;
	}
}

// Change the color gradient of the struct s_glb according to the value of key
// key can take value 1 to 6
void	shift_gradient(t_global *s_glb, int key)
{
	t_color	*begin;
	t_color	*end;
	int		fd;

	fd = open_grad(key);
	if (fd < 0)
		free_global_ex(s_glb, EXIT_FAILURE);
	begin = load_color(fd);
	end = load_color(fd);
	if (!begin || !end)
	{
		free_colors(begin, end);
		free_global_ex(s_glb, EXIT_FAILURE);
	}
	if (s_glb->s_fract->gradient)
		free_grad(s_glb->s_fract->gradient);
	s_glb->s_fract->gradient = bicolor_grad
		(begin, end, s_glb->s_fract->max_iter);
	if (close(fd) < 0)
	{
		perror("Close failed");
		free_global_ex(s_glb, EXIT_FAILURE);
	}
}

void			shift_init_point(t_global *s_glb, int key)
{
	double	r;
	double	i;

	r = s_glb->s_fract->s_init->r;
	i = s_glb->s_fract->s_init->i;
	free(s_glb->s_fract->s_init);
	if (key == 119) // Vers le haut
	{
		s_glb->s_fract->s_init = new_cpx_pt(r, i + 0.01);
	}
	if (key == 115) // Bas
	{
		s_glb->s_fract->s_init = new_cpx_pt(r, i - 0.01);
	}
	if (key == 97) // Gauche
	{
		s_glb->s_fract->s_init = new_cpx_pt(r - 0.01, i);
	}
	if (key == 100) // Droite
	{
		s_glb->s_fract->s_init = new_cpx_pt(r + 0.01, i);
	}
	if (!s_glb->s_fract->s_init)
		free_global_ex(s_glb, EXIT_FAILURE);	
}