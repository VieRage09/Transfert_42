/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:03:07 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 22:10:44 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>

# define WIDTH			1536
# define HEIGHT			864	 
# define FOV_VALUE		0.34
# define INSPACE			'!'

////////////////////////////////////////////// Structures utilitaires //////////

typedef enum e_keycode
{
	ESCAPE = 65307,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363,
	W_KEY = 119,
	S_KEY = 115,
	A_KEY = 97,
	D_KEY = 100
}t_keycode;

typedef struct s_pos
{
	int	xpos;
	int	ypos;
}t_pos;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////// Map related //////////

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*floor;
	char	*ceiling;
}	t_textures;

typedef struct s_map
{
	t_textures	s_texture;
	char		**map_tab;
	size_t		width;
	size_t		height;
}	t_map;

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////// MLX //////////

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////// Affichage //////////

typedef struct s_raycast
{
	t_vec	p_pos;
	t_vec	p_dir;
	t_vec	plane;

	t_vec	raydir;
	t_pos	p_map;
	t_vec	side_dist;
	t_vec	delta_dist;

	t_pos	step;

	bool	hit;
	int		side;
	double	w_dist;
}	t_raycast;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		ceilling;
	int		color;
	int		floor;
	int		tex_id;
}	t_draw;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

///////////////////////////////////////////////////////////////////////////////

typedef struct s_global
{
	t_mlx		*s_mlx;
	t_map		*s_map;
	t_raycast	*s_raycast;
	t_img_data	tex[4];
}t_global;

//-------------------------------------------------------------- PARSING -----//
// CHECK_MAP.C	
bool	check_map(t_map *s_map);

// CHECK_RGB.C
bool	check_rgb(char *line);

// CLEAN_UP.C
void	free_s_map(t_map *s_map);
void	destroy_texture(t_global *s_global);
void	free_s_mlx(t_global *s_global);
void	free_global(t_global *s_global);
void	free_global_exit(t_global *s_global, int exit_status);

// INIT_MAP_TAB.C
bool	init_map_tab(t_map *s_map, char *path, int fd);

// INIT_MAP_STRUCT.C
bool	init_s_map(t_map *s_map, char *path);

// INIT_OTHER.C
bool	load_textures(t_global *s_global);
bool	init_s_mlx(t_mlx *s_mlx);
bool	init_s_raycast(t_global *s_global);

//---------------------------------------------------------------------------//

// UTILS_1/2.C
int		ft_is_blanckline(char *str);
char	*free_strtrim(char *str, char *charset);
char	*trim_trail(char *str);
bool	find_player_spawn(char **map, t_pos *s_pos);
char	**copy_map(t_map *s_map);
bool	is_player_spawn(char c);
bool	is_valid(char c);
void	print_map(t_map *s_map);
bool	is_xpm(char *path);
bool	is_wspace(char c);

// ERRORS.C
void	manage_error(char *str_err);

//----------------------------------------------------------- EXECUTION -----//

// DRAW_FRAME.C
void	draw_frame(t_global *s_global);

// DRAW_LINE.C
void	draw_vertical_line(t_img_data *data, int x, t_global *s_global);

// GAME_LOOP.C
void	game_loop(t_global *s_global);

// MLX_UTILS.C
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

// PLAYER_MOVE.C
void	rotate_p_dir(t_raycast *s_raycast, int keycode, double angle);
bool	move_player(t_global *s_global, t_raycast *s_raycast, int keycode,
			double distance);
//---------------------------------------------------------------------------//

#endif