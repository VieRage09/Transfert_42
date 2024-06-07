/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 19:39:15 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	main(int ac, char *av[])
{
	t_global	*s_global;
	t_reso		s_reso;
	t_color		*begin_color;
	t_color		*end_color;

	menu(ac, av);
	begin_color = new_color(4, 97, 110);
	end_color = new_color(183, 215, 201);
	if (!begin_color || !end_color)
	{
		free_colors(begin_color, end_color);
		return (2);
	}
	set_reso(&s_reso, 960, 540);
	if (av[1][0] == 'm')
		s_global = new_global(new_cpx_pt(0, 0), &s_reso, ft_atoi(av[2]),
				bicolor_grad(begin_color, end_color, ft_atoi(av[2])));
	else
		s_global = new_global(new_cpx_pt(ft_atof(av[3]), ft_atof(av[4])),
				&s_reso, ft_atoi(av[2]),
				bicolor_grad(begin_color, end_color, ft_atoi(av[2])));
	if (!s_global)
		return (3);
	loop_hook(s_global);
	return (0);
}
