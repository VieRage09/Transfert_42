/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:10:24 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/24 17:12:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Malloc a struct t_monitor and assign s_param and philo_tab to it
// Returns 1 on failure
static int	init_monitor(t_monitor **s_monitor, t_param *s_param,
						t_philo **philo_tab)
{
	*s_monitor = malloc(sizeof(t_monitor));
	if (!*s_monitor)
		return (1);
	(*s_monitor)->s_param = s_param;
	(*s_monitor)->philo_tab = philo_tab;
	return (0);
}

// Calculates if the philo is dead of starvation or not
// Returns 1 on death, 0 on alive
static int	check_death(t_philo *s_philo)
{
	if (get_bool(&(s_philo->full), s_philo->full_mutx) == 1)
		return (0);
	if (get_timestamp(s_philo->s_param->starting_tv)
		- get_last_meal_ts(s_philo) >= s_philo->s_param->time_to_die)
	{
		set_bool(&s_philo->s_param->simulation_end, 1,
			s_philo->s_param->mutx_end);
		print_msg(s_philo, DIE);
		return (1);
	}
	return (0);
}

// Iterates over each philo of the tab and checks if he's dead
// Or if all philo are full
// Returns 1 if one of the conditions above is fulfilled
// Returns 0 otherwise
static int	check_full_death(t_monitor *s_monitor)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < s_monitor->s_param->philo_number
		&& get_bool(&(s_monitor->s_param->simulation_end),
			s_monitor->s_param->mutx_end) == 0)
	{
		if (check_death(s_monitor->philo_tab[i]) == 1)
			return (1);
		if (get_bool(&(s_monitor->philo_tab[i]->full),
				s_monitor->philo_tab[i]->full_mutx) == 1)
			full_count++;
		i++;
	}
	if (full_count == s_monitor->s_param->philo_number)
	{
		set_bool(&s_monitor->s_param->simulation_end, 1,
			s_monitor->s_param->mutx_end);
		return (1);
	}
	return (0);
}

// Waits until the beginning of the simulation
// Iterates over each philo of the tab and checks if he's dead
static void	*monitoring_routine(void *arg)
{
	t_monitor	*s_monitor;

	s_monitor = (t_monitor *)arg;
	while (get_bool(&(s_monitor->s_param->simulation_ready),
			s_monitor->s_param->mutx_ready) == 0)
		usleep(20);
	while (get_bool(&(s_monitor->s_param->simulation_end),
			s_monitor->s_param->mutx_end) == 0)
	{
		if (check_full_death(s_monitor) == 1)
			break ;
		usleep(20);
	}
	return (NULL);
}

// Creates the structure s_monitor and launch the monitor_thread
// When its done, set starting_tv to and the boolean simulation_ready to 1
int	launch_monitoring(pthread_t *monitor_thread, t_monitor **s_monitor,
			t_param *s_param, t_philo **philo_tab)
{
	if (init_monitor(s_monitor, s_param, philo_tab) != 0)
		return (1);
	if (pthread_create(monitor_thread, NULL, &monitoring_routine,
			(void *)(*s_monitor)) != 0)
		return (2);
	if (set_start_time(&s_param->starting_tv) != 0)
		return (3);
	set_bool(&s_param->simulation_ready, 1, s_param->mutx_ready);
	return (0);
}
