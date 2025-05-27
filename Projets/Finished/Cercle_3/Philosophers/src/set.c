/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:59:28 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/22 00:30:13 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Set start_tv to actual reel timestamp
int	set_start_time(struct timeval *start_tv)
{
	if (gettimeofday(start_tv, NULL) != 0)
		return (1);
	return (0);
}

// Sets the boolean value of bool pointer to value while protected by bool_mutex
void	set_bool(int *bool, int value, pthread_mutex_t *bool_mutex)
{
	pthread_mutex_lock(bool_mutex);
	*bool = value;
	pthread_mutex_unlock(bool_mutex);
}

// Sets last_meal_ts to value safely thanks to mutex
void	set_last_meal_ts(time_t *last_meal_ts, time_t value,
			pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*last_meal_ts = value;
	pthread_mutex_unlock(mutex);
}
