/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:03 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/07 21:04:59 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// Returns gradient size
int	grad_size(t_color **grad)
{
	int	size;

	size = 0;
	while (grad[size])
		size++;
	return (size);
}

// Looks into the color gradient and returns the correct hexacolor using 
// iteration number and max iteration number
int	get_color_grad(int iter, int max_iter, t_color **grad, int grad_len)
{
	double	ratio;
	int		i;

	ratio = (double)iter / (double)max_iter;
	i = grad_len * ratio;
	if (ratio == 1)
		return (0);
	return (create_trgb(255, grad[i]->r, grad[i]->g, grad[i]->b));
}

//Loads a bicolor gradient of n colors via linear interpolation
t_color	**bicolor_grad(t_color *start, t_color *end, int n)
{
	t_color	**tab;
	int		i;
	double	rdiff;
	double	gdiff;
	double	bdiff;

	tab = malloc((n + 1) * sizeof(t_color *));
	if (!tab)
	{
		perror("Malloc failed");
		return (NULL);
	}
	i = 0;
	rdiff = (double)(start->r - end->r) / (double)n;
	gdiff = (double)(start->g - end->g) / (double)n;
	bdiff = (double)(start->b - end->b) / (double)n;
	while (i < n)
	{
		tab[i] = new_color(start->r - rdiff * i, start->g - gdiff * i,
				start->b - bdiff * i);
		i++;
	}
	free_colors(start, end);
	tab[i] = NULL;
	return (tab);
}

void	free_grad(t_color **grad)
{
	int	i;

	i = 0;
	while (grad[i])
	{
		free(grad[i]);
		i++;
	}
	free(grad);
}
