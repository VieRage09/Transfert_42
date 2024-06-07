/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/05 20:58:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	main(int ac, char *av[])
{
	t_global	*s_global;
	t_reso		s_reso;

	menu(ac, av);
	set_reso(&s_reso, 960, 540);
	if (av[1][0] == 'm')
		s_global = new_global(new_cpx_pt(0, 0), &s_reso, ft_atoi(av[2]),
				bicolor_grad(new_color(80, 80, 255), new_color(255, 151, 236), 50));
	else
		s_global = new_global(new_cpx_pt(ft_atof(av[3]), ft_atof(av[4])),
				&s_reso, ft_atoi(av[2]), bicolor_grad(new_color(80, 80, 255), new_color(255, 151, 236), 150));
	if (!s_global)
		return (1);
	loop_hook(s_global);
	return (0);
}
