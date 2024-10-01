/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:22 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/23 21:54:18 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Creates a thread_tab containing the pointers of each thread (philo)
// Then launch them all and also the monitoring_thread
// Finnally joins all the threads created and free thread_tab
static int	multiple_philo_simulation(pthread_t *monitor_thread,
		t_monitor **s_monitor, t_param *s_param, t_philo **philo_tab)
{
	pthread_t	*thread_tab;
	int			i;

	thread_tab = malloc(s_param->philo_number * sizeof(pthread_t));
	if (!thread_tab)
		return (1);
	i = -1;
	while (++i < s_param->philo_number)
	{
		if (pthread_create(&thread_tab[i], NULL, &philo_routine,
				philo_tab[i]) != 0)
			return (2);
	}
	if (launch_monitoring(monitor_thread, s_monitor, s_param, philo_tab) != 0)
		return (3);
	i = -1;
	while (++i < s_param->philo_number)
	{
		if (pthread_join(thread_tab[i], NULL) != 0)
			return (5);
	}
	if (pthread_join(*monitor_thread, NULL) != 0)
		return (6);
	free(thread_tab);
	return (0);
}

// Handles the case when there is only 1 philo at the table
static void	*lone_philo_routine(void *arg)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)arg;
	while (get_bool(&(s_philo->s_param->simulation_ready),
			s_philo->s_param->mutx_ready) == 0)
		usleep(20);
	print_msg(s_philo, FORK);
	frag_usleep(s_philo, s_philo->s_param->time_to_die);
	return (NULL);
}

// Launch the simulation when there is only 1 philo at the table
int	lone_philo_simulation(pthread_t *monitor_thread, t_monitor **s_monitor,
							t_param *s_param, t_philo **philo_tab)
{
	pthread_t	*thread_tab;

	thread_tab = malloc(sizeof(pthread_t));
	if (!thread_tab)
		return (1);
	if (pthread_create(thread_tab, NULL, &lone_philo_routine,
			philo_tab[0]) != 0)
		return (2);
	if (launch_monitoring(monitor_thread, s_monitor, s_param, philo_tab) != 0)
		return (3);
	if (pthread_join(*thread_tab, NULL) != 0)
		return (5);
	if (pthread_join(*monitor_thread, NULL) != 0)
		return (6);
	free(thread_tab);
	return (0);
}

// Launch the solo philo is there is only 1 philo at the table
// Otherwise, launch the regular simulation
// Return 0 on success, 1 or 2 on failure of the simulation functions
int	launch_simulation(pthread_t *monitor_thread,
		t_monitor **s_monitor, t_param *s_param, t_philo **philo_tab)
{
	if (s_param->philo_number == 1)
	{
		if (lone_philo_simulation(monitor_thread, s_monitor,
				s_param, philo_tab) != 0)
			return (1);
	}
	else
	{
		if (multiple_philo_simulation(monitor_thread, s_monitor,
				s_param, philo_tab) != 0)
			return (2);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_param			s_param;
	pthread_mutex_t	*fork_tab;
	t_philo			**philo_tab;
	pthread_t		monitor_thread;
	t_monitor		*s_monitor;

	if (initialization(ac, av, &s_param, &fork_tab) != 0)
		return (EXIT_FAILURE);
	if (init_philo_tab(&philo_tab, &s_param, fork_tab) != 0)
	{
		destroy_fork_tab(fork_tab, s_param.philo_number);
		destroy_param(&s_param);
	}
	if (launch_simulation(&monitor_thread, &s_monitor,
			&s_param, philo_tab) != 0)
	{
		clean_everything(fork_tab, philo_tab, &s_param, s_monitor);
		return (EXIT_FAILURE);
	}
	clean_everything(fork_tab, philo_tab, &s_param, s_monitor);
	return (EXIT_SUCCESS);
}
