/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:17:23 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/23 21:58:48 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Mallocs and initialize the mutex of structure s_philo
// Returns 0 on succes
static int	create_philo_mutex(t_philo *s_philo)
{
	s_philo->last_meal_mutx = malloc(sizeof(pthread_mutex_t));
	if (!s_philo->last_meal_mutx)
		return (1);
	s_philo->full_mutx = malloc(sizeof(pthread_mutex_t));
	if (!s_philo->full_mutx)
		return (2);
	if (pthread_mutex_init(s_philo->last_meal_mutx, NULL) != 0)
		return (3);
	if (pthread_mutex_init(s_philo->full_mutx, NULL) != 0)
		return (4);
	return (0);
}

// Creates and return an s_philo pointer
// Assign number and forks according to its position in the philo_tab
static t_philo	*create_philo(int position, t_param *s_param,
							pthread_mutex_t *fork_tab)
{
	t_philo	*s_philo;

	s_philo = malloc(sizeof(t_philo));
	if (!s_philo)
		return (NULL);
	if (create_philo_mutex(s_philo) != 0)
		return (NULL);
	s_philo->number = position + 1;
	s_philo->s_param = s_param;
	if (s_philo->number == s_param->philo_number)
	{
		s_philo->l_fork = &fork_tab[position];
		s_philo->r_fork = &fork_tab[0];
	}
	else
	{
		s_philo->l_fork = &fork_tab[position];
		s_philo->r_fork = &fork_tab[position + 1];
	}
	s_philo->last_meal_ts = 0;
	s_philo->meal_eaten = 0;
	s_philo->full = 0;
	return (s_philo);
}

// Creates and return an s_philo pointer with only 1 fork
// His r_fork points to NULL
static t_philo	*create_lone_philo(t_param *s_param, pthread_mutex_t *fork_tab)
{
	t_philo	*s_philo;

	s_philo = malloc(sizeof(t_philo));
	if (!s_philo)
		return (NULL);
	s_philo->last_meal_mutx = malloc(sizeof(pthread_mutex_t));
	s_philo->full_mutx = malloc(sizeof(pthread_mutex_t));
	if (!s_philo->last_meal_mutx || !s_philo->full_mutx)
		return (NULL);
	if (pthread_mutex_init(s_philo->last_meal_mutx, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(s_philo->full_mutx, NULL) != 0)
		return (NULL);
	s_philo->number = 1;
	s_philo->s_param = s_param;
	s_philo->l_fork = &fork_tab[0];
	s_philo->r_fork = NULL;
	s_philo->last_meal_ts = 0;
	s_philo->meal_eaten = 0;
	s_philo->full = 0;
	return (s_philo);
}

// Inits philo_tab :
// Each philosopher has the same s_param and gets a number
// and 2 associated forks according to its position inside the tab
int	init_philo_tab(t_philo ***philo_tab, t_param *s_param,
					pthread_mutex_t *fork_tab)
{
	int	i;

	*philo_tab = malloc(s_param->philo_number * sizeof(t_philo *));
	if (!*philo_tab)
		return (1);
	i = 0;
	while (i < s_param->philo_number)
	{
		if (s_param->philo_number == 1)
			(*philo_tab)[i] = create_lone_philo(s_param, fork_tab);
		else
			(*philo_tab)[i] = create_philo(i, s_param, fork_tab);
		if (!(*philo_tab)[i])
		{
			free_philo_tab(*philo_tab, i);
			return (2);
		}
		i++;
	}
	return (0);
}
