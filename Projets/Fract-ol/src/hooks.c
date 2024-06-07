/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 00:32:50 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 22:06:56 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Make an action when a specific key is pressed :
// ESC : quit the program
// Arrow key : shift the frame to the direction of the key
// + - : increases of lowers the nu,ber of iterations of the fractal calculation
// 1 to 6 : choose the color gradient associated with the key
int	handle_keyhook(int keycode, t_global *s_glb)
{
	if (keycode == 65307)
		free_global_ex(s_glb, EXIT_SUCCESS);
	else if (keycode == 65361)
		shift_frame(s_glb, 'w');
	else if (keycode == 65362)
		shift_frame(s_glb, 'n');
	else if (keycode == 65363)
		shift_frame(s_glb, 'e');
	else if (keycode == 65364)
		shift_frame(s_glb, 's');
	else if (keycode == 65451)
			s_glb->s_fract->max_iter += 10;
	else if (keycode == 65453 && s_glb->s_fract->max_iter > 10)
		s_glb->s_fract->max_iter -= 10;
	else if (keycode == 49 || keycode == 50 || keycode == 51
		|| keycode == 52 || keycode == 53 || keycode == 54)
		shift_gradient(s_glb, keycode - 48);
	else if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		shift_init_point(s_glb, keycode);
	refresh_img(s_glb);
	return (1);
}

// Destroys window when hook redcross is pressed
int	cross_button_hook(t_global *s_glb)
{
	free_global_ex(s_glb, EXIT_SUCCESS);
	return (1);
}

// Zooms in and out, recreating the image according to the input
int	zoom_hook(int button, int x, int y, t_global *s_glb)
{
	if (button == 4)
		set_frame_zoom(s_glb, 1.1, x, y);
	else if (button == 5)
		set_frame_zoom(s_glb, 0.9, x, y);
	refresh_img(s_glb);
	return (1);
}

// Loop function. Waits for any intput and redirects to the 
// the correct function
void	loop_hook(t_global *s_global)
{
	draw_julman(s_global->s_img, s_global->s_fract);
	mlx_put_image_to_window(s_global->s_mlx->mlx, s_global->s_mlx->win,
		s_global->s_img->img, 0, 0);
	mlx_hook(s_global->s_mlx->win, 3, 1L << 1, handle_keyhook, s_global);
	mlx_hook(s_global->s_mlx->win, 17, 0L, cross_button_hook, s_global);
	mlx_hook(s_global->s_mlx->win, 4, 1L << 2, zoom_hook, s_global);
	mlx_loop(s_global->s_mlx->mlx);
}
