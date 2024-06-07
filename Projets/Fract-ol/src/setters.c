/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:46:23 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/05 21:47:02 by tlebon           ###   ########.fr       */
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
