/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:05:03 by tlebon            #+#    #+#             */
/*   Updated: 2024/06/05 21:40:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// static t_color	*load_color(int fd)
// {
// 	int		rgb[3];
// 	int		i;
// 	char	*buff;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		buff = get_next_line(fd);
// 		if (!buff)
// 			return (NULL);
// 		rgb[i] = ft_atoi(buff);
// 		free(buff);
// 		i++;
// 	}
// 	return (new_color(rgb[0], rgb[1], rgb[2]));
// }

// Supposed to load color values from a file and store them in an t_color tab
// A SECURISER 
// Fonction delaissee pour l'instant
// t_color	**load_grad_stops(int fd, int stop_nb)
// {
// 	int		i;
// 	char	*buff;
// 	t_color	**grad;

// 	grad = malloc((stop_nb + 1) * sizeof(t_color *));
// 	if (!grad)
// 		return (NULL);
// 	i = 0;
// 	buff = NULL;
// 	while (i < stop_nb)
// 	{
// 		buff = get_next_line(fd);
// 		if (buff[0] != '#')
// 		{
// 			free(buff);
// 			free(grad);
// 			printf("Wrong gradient file structure !\n");
// 			return (NULL);
// 		}
// 		free(buff);
// 		grad[i] = load_color(fd);
// 		i++;
// 	}
// 	grad[i] = NULL;
// 	return (grad);
// }

// Returns gradient size
int	grad_size(t_color **grad)
{
	int	size;

	size = 0;
	while (grad[size])
		size++;
	return (size);
}

// According to the colors of grad, returns a color value
// as an int, gradient wise

// int	get_color_grad(int iter, int max_iter, t_color **grad, int grad_len)
// {
// 	double	ratio;
// 	double	red;
// 	double	green;
// 	double	blue;
// 	int		i;

// 	ratio = (double)iter / (double)max_iter;
// 	if (ratio == 1)
// 		return (0);
// 	i = ratio * (grad_len - 1);
// 	red = grad[i]->r + (grad[i + 1]->r - grad[i]->r) * (ratio);
// 	green = grad[i]->g + (grad[i + 1]->g - grad[i]->g) * (ratio);
// 	blue = grad[i]->b + (grad[i + 1]->b - grad[i]->b) * (ratio);
// 	return (create_trgb(255, (int)red, (int)green, (int)blue));
// }

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
// returns a color according to trigonometric functions and ratio of iter / max_iter
// int	get_color(int iter, int max_iter)
// {
// 	double	red;
// 	double	green;
// 	double	blue;
// 	double	ratio;

// 	ratio = iter / max_iter;
// 	red = sin(ratio);
// 	green = cos(ratio);
// 	blue = -sin(ratio);
// 	return (create_trgb(255, 255 * red, 255 * green, 255 * blue));
// }

//Loads a bicolor gradient of n colors via linear interpolation
t_color	**bicolor_grad(t_color *start, t_color *end, int n)
{
	t_color	**tab;
	int		i;
	double		rdiff;
	double		gdiff;
	double		bdiff;

	tab = malloc((n + 1) * sizeof(t_color *));
	if (!tab)
		return (NULL);
	i = 0;
	rdiff = (double)(start->r - end->r) / (double)n;
	gdiff = (double)(start->g - end->g) / (double)n;
	bdiff = (double)(start->b - end->b) / (double)n;
	while (i < n)
	{
		tab[i] = new_color(start->r - rdiff * i, start->g - gdiff * i, start->b - bdiff * i);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

// Experimentation not finished
// t_color	**create_gradient(t_color **grad_stops)
// {
// 	t_color	**gradient;
// 	int		curstop;
	
// 	gradient = malloc((sizeof(t_color *) * (grad_size(grad_stops) - 1)) * 256);
// 	if (!gradient)
// 		return (NULL);
// 	curstop = 0;
// 	while (curstop < grad_size(grad_stops) - 1)
// 	{
// 		gradient = bicolor_grad(grad_stops[curstop], grad_stops[curstop + 1]);
// 		curstop++;
// 		gradient += 256; // ??????? Je ne pense pas que ca marche, l'idee est de decaler le pointeur
// 		// tout en pouvant retourner le debut a la fin de la fonction
// 	}
// 	return (gradient);
// }

// Les deux dernieres fonction jcp si elles marchent mais je pense que c'est la bonne voie