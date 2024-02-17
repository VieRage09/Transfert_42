/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:07:14 by tlebon            #+#    #+#             */
/*   Updated: 2024/02/17 16:58:40 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"libs/mlx/mlx.h"
#include"libs/libft/libft.h"

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;	
}t_mlx_data;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}t_img_data;

#endif