/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:28:06 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/25 21:09:28 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int ft_atoi(const char *nptr)
{
	int i;
	int nbr;
	int sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign = sign * (-1);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * nbr);
}

int *menu(int ac, char **av)
{
	// ARGS :
	// av[1] = number of philo
	// av[2] (ms) = time before death if philo hasn't eat
	// av[3] (ms) = time to eat
	// av[4] (ms) = time of sleep
	// av[5] (optional) = number of meal before prog stops
	int *tab;
	int i;

	tab = malloc((ac - 1) * sizeof(int));
	if (!tab)
		return (NULL);
	i = 0;
	while (av[i])
	{
		tab[i] = ft_atoi(av[i]);
		i++;
	}
	return (tab);
}

pthread_t	*create_threads(int *infos_tab)
{
	int			i;
	pthread_t	*philo_tab;
	
	philo_tab = malloc((infos_tab[0] + 1) * sizeof(pthread_t));
	if (!philo_tab)
		return (NULL);
	i = 0;
	while (i < infos_tab[0])
	{
		if (pthread_create())
	}
}

int main(int ac, char **av)
{
	int *infos_tab;
	pthread_t	*philo_tab;

	if (ac < 5)
		printf("This program needs 4 to 5 arguments :\n	- Number of philosophers\n	- Time to die\n	- Time to eat\n	- Time to sleep\n	- [Number of times each philosophers must eat]\n");
	else
		infos_tab = menu(ac, av);
	philo_tab = create_threads(infos_tab);
	return (EXIT_SUCCESS);
}

// 1. Recuperation des inputs et verification
// 2. Creation des threads en fonction du nbr de philo
// 3. Lancement de la simulation