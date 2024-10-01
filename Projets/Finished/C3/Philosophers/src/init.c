/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:01:18 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/23 21:52:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../philo.h"

// Checks for the correct number of arguments
static int	check_inputs(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Philo takes 4 to 5 arguments\n");
		return (1);
	}
	return (0);
}

// Malloc and initialize the mutex of s_param
static int	init_param_mutx(t_param *s_param)
{
	s_param->mutx_ready = malloc(sizeof(pthread_mutex_t));
	s_param->mutx_end = malloc(sizeof(pthread_mutex_t));
	s_param->mutx_write = malloc(sizeof(pthread_mutex_t));
	if (!s_param->mutx_ready || !s_param->mutx_end || !s_param->mutx_write)
		return (1);
	if (pthread_mutex_init(s_param->mutx_ready, NULL) != 0)
		return (2);
	if (pthread_mutex_init(s_param->mutx_end, NULL) != 0)
		return (3);
	if (pthread_mutex_init(s_param->mutx_write, NULL) != 0)
		return (4);
	return (0);
}

// Checks for correct input then initialize the s_param struct
// with corresponding data
static int	init_s_param(int ac, char **av, t_param *s_param)
{
	if (check_inputs(ac) != 0)
		return (1);
	s_param->philo_number = ft_atoi(av[1]);
	s_param->time_to_die = ft_atoi(av[2]);
	s_param->time_to_eat = ft_atoi(av[3]);
	s_param->time_to_sleep = ft_atoi(av[4]);
	s_param->meal_number = 1;
	if (ac == 6)
		s_param->meal_number = ft_atoi(av[5]);
	if (s_param->philo_number <= 0 || s_param->time_to_die <= 0
		|| s_param->time_to_eat <= 0 || s_param->time_to_sleep <= 0
		|| s_param->meal_number <= 0)
	{
		printf("Parameters must be positif integers\n");
		return (2);
	}
	if (ac != 6)
		s_param->meal_number = -1;
	s_param->simulation_ready = 0;
	s_param->simulation_end = 0;
	if (init_param_mutx(s_param) != 0)
		return (4);
	return (0);
}

// Init all the mutex of fork_tab
// Return 0 on success, -1 on malloc failed
// Returns the position (i) of failed mutex_init
static int	init_fork_tab(pthread_mutex_t **fork_tab, t_param *s_param)
{
	int	i;

	*fork_tab = malloc(s_param->philo_number * sizeof(pthread_mutex_t));
	if (!*fork_tab)
		return (-1);
	i = 0;
	while (i < s_param->philo_number)
	{
		if (pthread_mutex_init(&(*fork_tab)[i], NULL) != 0)
			return (i);
		i++;
	}
	return (0);
}

// Initialize s_param and fork_tab
int	initialization(int ac, char **av, t_param *s_param,
	pthread_mutex_t **fork_tab)
{
	int	error_value;

	if (init_s_param(ac, av, s_param) != 0)
		return (1);
	error_value = init_fork_tab(fork_tab, s_param);
	if (error_value != 0)
	{
		destroy_fork_tab(*fork_tab, error_value);
		free(s_param);
		return (2);
	}
	return (0);
}
