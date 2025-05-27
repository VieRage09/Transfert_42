/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:23:54 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 21:59:01 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Returns a pointer to a struct containing the x and y position of a point
t_cpx_pt	*new_cpx_pt(double reel, double imaginary)
{
	t_cpx_pt	*s_cpx_pt;

	s_cpx_pt = malloc(sizeof(t_cpx_pt));
	if (!s_cpx_pt)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_cpx_pt->r = reel;
	s_cpx_pt->rxr = reel * reel;
	s_cpx_pt->i = imaginary;
	s_cpx_pt->ixi = imaginary * imaginary;
	return (s_cpx_pt);
}

// Returns a pointer to a struct containing rgb values of a color
t_color	*new_color(int r, int g, int b)
{
	t_color	*s_color;

	s_color = malloc(sizeof(t_color));
	if (!s_color)
	{
		perror("Malloc failed");
		return (NULL);
	}
	s_color->r = r;
	s_color->g = g;
	s_color->b = b;
	return (s_color);
}

// Frees the color structs in parameter if they exist
void	free_colors(t_color *begin_color, t_color *end_color)
{
	if (begin_color)
		free(begin_color);
	if (end_color)
		free(end_color);
}

// Frees the pointers inside a fract struct and frees it too
void	free_fract(t_fract *s_fract)
{
	if (s_fract)
	{
		if (s_fract->s_frame)
			free(s_fract->s_frame);
		if (s_fract->s_init)
			free(s_fract->s_init);
		if (s_fract->gradient)
			free_grad(s_fract->gradient);
		free(s_fract);
	}
}

// Frees the pointers inside s global struct and frees it too
// then exit with status status
void	*free_global_ex(t_global *s_global, int status)
{
	if (s_global)
	{
		free_fract(s_global->s_fract);
		if (s_global->s_img)
		{
			if (s_global->s_img->img)
				mlx_destroy_image(s_global->s_mlx->mlx, s_global->s_img->img);
			free(s_global->s_img);
		}
		if (s_global->s_mlx)
		{
			if (s_global->s_mlx->win)
				mlx_destroy_window(s_global->s_mlx->mlx, s_global->s_mlx->win);
			if (s_global->s_mlx->mlx)
			{
				mlx_destroy_display(s_global->s_mlx->mlx);
				free(s_global->s_mlx->mlx);
			}
			free(s_global->s_mlx);
		}
		free(s_global);
	}
	exit(status);
}
