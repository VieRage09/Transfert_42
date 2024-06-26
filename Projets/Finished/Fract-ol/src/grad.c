/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:03 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/20 17:48:41 by tlebon           ###   ########.fr       */
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

// Opens the file corresponding to the value of key : from 1 to 6
// Returns the fd openned or -1 on error
int	open_grad(int key)
{
	int		fd;

	if (key == 1)
		fd = open("gradients/grad_1.txt", O_RDONLY);
	else if (key == 2)
		fd = open("gradients/grad_2.txt", O_RDONLY);
	else if (key == 3)
		fd = open("gradients/grad_3.txt", O_RDONLY);
	else if (key == 4)
		fd = open("gradients/grad_4.txt", O_RDONLY);
	else if (key == 5)
		fd = open("gradients/grad_5.txt", O_RDONLY);
	else if (key == 6)
		fd = open("gradients/grad_6.txt", O_RDONLY);
	else
		return (-1);
	if (fd < 0)
		perror("Open failed");
	return (fd);
}

// Looks into the color gradient and returns the correct hexacolor using 
// iteration number and max iteration number ratio
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
t_color	**line_grad(t_color *start, t_color *end, int n)
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

// Frees properly the grad double pointer
void	free_grad(t_color **grad)
{
	int	i;

	if (!grad)
		return ;
	i = 0;
	while (grad[i])
	{
		free(grad[i]);
		i++;
	}
	free(grad);
}
