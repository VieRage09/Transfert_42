/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:58:52 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/23 21:50:48 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Returns the actual timestamp since the beginning of the simulation in ms
time_t	get_timestamp(struct timeval start_tv)
{
	struct timeval	tv;
	time_t			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec - start_tv.tv_sec) * 1000
		+ (tv.tv_usec - start_tv.tv_usec) / 1000;
	return (timestamp);
}

// Gets the boolean value of bool protected by bool_mutex
int	get_bool(int *bool, pthread_mutex_t *bool_mutex)
{
	int	value;

	pthread_mutex_lock(bool_mutex);
	value = *bool;
	pthread_mutex_unlock(bool_mutex);
	return (value);
}

// Returns the value of last_meal_ts safely (mutx)
time_t	get_last_meal_ts(t_philo *s_philo)
{
	time_t	last_meal_ts;

	pthread_mutex_lock(s_philo->last_meal_mutx);
	last_meal_ts = s_philo->last_meal_ts;
	pthread_mutex_unlock(s_philo->last_meal_mutx);
	return (last_meal_ts);
}
