/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:03:02 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/23 21:50:30 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Free/destroys the structures inside philo_tab (according to size)
// then free the tab
void	free_philo_tab(t_philo **philo_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_mutex_destroy(philo_tab[i]->last_meal_mutx) != 0)
			return ;
		if (pthread_mutex_destroy(philo_tab[i]->full_mutx) != 0)
			return ;
		free(philo_tab[i]->last_meal_mutx);
		free(philo_tab[i]->full_mutx);
		free(philo_tab[i]);
		i++;
	}
	free(philo_tab);
}

// Destroys the initialized mutex of fork_tab then frees fork_tab
void	destroy_fork_tab(pthread_mutex_t *fork_tab,
			int initialized_mutex_number)
{
	int	i;

	if (initialized_mutex_number > 0)
	{
		i = 0;
		while (i < initialized_mutex_number)
		{
			if (pthread_mutex_destroy(&fork_tab[i]) != 0)
				printf("Failed to destroy mutex %i of fork_tab\n", i);
			i++;
		}
	}
	free(fork_tab);
}

// Destroys the mutexs of s_param and free their pointer
void	destroy_param(t_param *s_param)
{
	pthread_mutex_destroy(s_param->mutx_ready);
	pthread_mutex_destroy(s_param->mutx_end);
	pthread_mutex_destroy(s_param->mutx_write);
	free(s_param->mutx_ready);
	free(s_param->mutx_end);
	free(s_param->mutx_write);
}

// Free everything that is malloced and
// destroys every mutex initialized
void	clean_everything(pthread_mutex_t *fork_tab, t_philo **philo_tab,
							t_param *s_param, t_monitor *s_monitor)
{
	destroy_fork_tab(fork_tab, s_param->philo_number);
	free_philo_tab(philo_tab, s_param->philo_number);
	destroy_param(s_param);
	free(s_monitor);
}
