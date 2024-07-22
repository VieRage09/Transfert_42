/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:07:14 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/20 17:48:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include<stdio.h> // for perror
# include<errno.h> // for perror
# include<fcntl.h> // for open
# include<limits.h> // for INT_MAX
# include<math.h>
# include"libs/mlx/mlx.h" // duh
# include"libs/libft/libft.h" // duh

// Contains pointers to mlx and to win
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;	
}t_mlx_data;

// X and Y resolution
typedef struct s_reso
{
	int	x_reso;
	int	y_reso;
}t_reso;

// Contain pointer to img and some infos about the img
typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
	t_reso	*s_reso;
}t_img_data;

// A point on a plane, complex too
typedef struct s_cpx_pt
{
	double	r;
	double	rxr;
	double	i;
	double	ixi;
}t_cpx_pt;

// Define the boundaries of the complex plane
typedef struct s_frame
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;	
}t_frame;

// Define rgb value of a color
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}t_color;

//Infos about the fractal we wanna draw
typedef struct s_fract
{
	double		zoom_x;
	double		zoom_y;
	int			max_iter;
	t_color		**gradient;
	t_cpx_pt	*s_init;
	t_frame		*s_frame;
}t_fract;

// Regroups everyting
typedef struct s_global
{
	t_mlx_data	*s_mlx;
	t_img_data	*s_img;
	t_fract		*s_fract;
}t_global;

// Constructors 		5 V

t_mlx_data		*new_mlx_data(t_reso *s_reso, char *win_name);
t_img_data		*new_img_data(t_mlx_data *s_mlx, t_reso *s_reso);
t_fract			*new_fract(t_cpx_pt *s_init, t_reso *s_reso, int max_iter,
					t_color **grad);
t_global		*new_global(t_cpx_pt *s_init, t_reso *s_reso, int max_iter,
					t_color **grad);
t_frame			*new_frame(double x1, double x2, double y1, double y2);

// Constructors_utils	5 

t_cpx_pt		*new_cpx_pt(double reel, double imaginary);
t_color			*new_color(int r, int g, int b);
void			free_colors(t_color *begin_color, t_color *end_color);
void			*free_global_ex(t_global *s_global, int status);
void			free_fract(t_fract *s_fract);

// Utils				5 V menu a bien securiser
void			menu(int ac, char *av[]);
int				create_trgb(int t, int r, int g, int b);
void			put_pixel_to_image(t_img_data *s_img, int x, int y, int color);
t_color			*load_color(int fd);
char			*str_append(char *s1, char *s2);

// Grad					5

int				grad_size(t_color **grad);
int				open_grad(int key);
int				get_color_grad(int iter, int max_iter, t_color **grad,
					int grad_len);
t_color			**line_grad(t_color *start, t_color *end, int n);
void			free_grad(t_color **grad);

// Setters 				5 V

void			set_reso(t_reso *s_reso, int x_reso, int y_reso);
void			set_frame_zoom(t_global *s_glb, double zoom,
					int x_pos, int y_pos);
void			shift_frame(t_global *s_glb, char dir);
void			shift_gradient(t_global *s_glb, int key);
void			shift_init_point(t_global *s_glb, int key);

// Hooks				4 V

int				handle_keyhook(int keycode, t_global *s_glb);
int				cross_button_hook(t_global *s_glb);
int				zoom_hook(int x, int y, int button, t_global *s_glb);
void			loop_hook(t_global *s_global);

// Fractal				5 V

int				man_pt_check(t_cpx_pt *s_cpx_pt, double x, double y,
					int max_iter);
int				jul_pt_check(t_cpx_pt *s_init, double x, double y,
					int max_iter);
int				draw_julman(t_img_data *s_img, t_fract *s_fract);
int				refresh_infos(t_global *s_glb);
int				refresh_img(t_global *s_glb);

///////////////////////////

#endif