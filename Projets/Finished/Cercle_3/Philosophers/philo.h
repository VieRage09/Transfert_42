/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:29:02 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/23 21:51:36 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>	  // for memset
# include <stdio.h>	  // for printf
# include <stdlib.h>	  // for malloc
# include <unistd.h>	  // for write usleep
# include <sys/time.h> // for gettimeofday
# include <pthread.h>  // for pthread functions

typedef enum e_msg
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}t_msg;

typedef enum e_mutx_handler
{
	LOCK,
	UNLOCK
}t_mutx_handler;

typedef struct s_param
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_number;

	struct timeval	starting_tv;

	int				simulation_ready;
	int				simulation_end;

	pthread_mutex_t	*mutx_ready;
	pthread_mutex_t	*mutx_end;

	pthread_mutex_t	*mutx_write;
}t_param;

typedef struct s_philo
{
	t_param			*s_param;

	int				number;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				meal_eaten;

	time_t			last_meal_ts;
	pthread_mutex_t	*last_meal_mutx;

	int				full;
	pthread_mutex_t	*full_mutx;
}t_philo;

typedef struct s_monitor
{
	t_param	*s_param;
	t_philo	**philo_tab;
}t_monitor;

//	CLEAN.C			4	V
void	free_philo_tab(t_philo **philo_tab, int size);
void	destroy_fork_tab(pthread_mutex_t *fork_tab,
			int initialized_mutex_number);
void	destroy_param(t_param *s_param);
void	clean_everything(pthread_mutex_t *fork_tab, t_philo **philo_tab,
			t_param *s_param, t_monitor *s_monitor);

// GET.C			3	V
time_t	get_timestamp(struct timeval start_tv);
int		get_bool(int *bool, pthread_mutex_t *bool_mutex);
time_t	get_last_meal_ts(t_philo *s_philo);

// INIT.C			5	V
int		initialization(int ac, char **av, t_param *s_param,
			pthread_mutex_t **fork_tab);

//	MONITORING.C	5	V
int		launch_monitoring(pthread_t *monitor_thread, t_monitor **s_monitor,
			t_param *s_param, t_philo **philo_tab);

// PHILO_TAB.C		4	V
int		init_philo_tab(t_philo ***philo_tab, t_param *s_param,
			pthread_mutex_t *fork_tab);

//ROUTINE.C			5	V
void	*philo_routine(void *arg);

// SET.C			3	V
int		set_start_time(struct timeval *start_tv);
void	set_bool(int *bool, int value, pthread_mutex_t *bool_mutex);
void	set_last_meal_ts(time_t *last_meal_ts, time_t value,
			pthread_mutex_t *mutex);

// UTILS.C		5	V
int		ft_atoi(const char *nptr);
void	frag_usleep(t_philo *s_philo, int value);
void	print_msg(t_philo *s_philo, t_msg status);

#endif