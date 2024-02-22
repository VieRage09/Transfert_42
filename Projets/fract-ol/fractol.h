/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:07:14 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/22 03:36:55 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
#include<stdio.h>
//
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"libs/mlx/mlx.h"
#include"libs/libft/libft.h"

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct s_cpx_pt
{
	double	r;
	double	i;	
}t_cpx_pt;

//Definit la plage du plan complex a afficher, peut deformer la fractale
typedef struct	s_frame
{
	double	x1;
	double	x2;
	
	double	y1;
	double	y2;

	double	zoom_x;
	double	zoom_y;
}t_frame;

typedef struct s_reso
{
	int	x_reso;
	int	y_reso;
}t_reso;

typedef struct	s_mlx_data
{
	void	*mlx;
	void	*win;	
}t_mlx_data;

typedef struct	s_img_data
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}t_img_data;

// Constructors
int		mlx_data_struct_constructor(t_mlx_data *s_mlx, t_reso *s_reso, char *win_name);
int		img_data_struct_constructor(t_mlx_data *s_mlx, t_img_data *s_img, t_reso *s_reso);
void	set_cpx_pt_struct(t_cpx_pt *s_cpx_pt, double reel, double imaginary);
void	set_frame_struct(t_frame *s_frame, char c, int x_size, int y_size);
void	set_reso_struct(t_reso *s_reso, int x_reso, int y_reso);

// Utils
int		create_trgb(int t, int r, int g, int b);
void	put_pixel_to_image(t_img_data *s_img, int x, int y, int color);
int		menu (int ac, char *av[]);

// Hooks
int		escape_keyhook(int keycode, t_mlx_data *s_mlx);
int		cross_button_hook(t_mlx_data *s_mlx);

// Fractal
int		draw_julman(t_img_data *s_img, t_reso *s_reso, int max_iter);
int		julman_pt_check(t_cpx_pt *s_cpx_pt, double x, double y, int max_iter);

#endif