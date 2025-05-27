/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:48:29 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/24 17:12:53 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Takes care of locking the correct forks in the correct order according to 
// the oddness of the philo number
// Locks the mutx and prints the fork msg for LOCK
// Unlocks the mutx in the right order if UNLOCK
static void	handle_forks(t_philo *s_philo, t_mutx_handler e_handler)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (s_philo->number % 2 == 0)
	{
		first = s_philo->r_fork;
		second = s_philo->l_fork;
	}
	else
	{
		first = s_philo->l_fork;
		second = s_philo->r_fork;
	}
	if (e_handler == LOCK)
	{
		pthread_mutex_lock(first);
		print_msg(s_philo, FORK);
		pthread_mutex_lock(second);
		print_msg(s_philo, FORK);
	}
	else if (e_handler == UNLOCK)
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
	}
}

// Eating routine :
// Locks both forks needed, set the last_meal timestamp accordingly,
// increments meal_eaten, prints the msg and sleeps the correct time
// Turn the boolean full to 1 if needed
// When finished, unlock both forks
static int	philo_eat(t_philo *s_philo)
{
	handle_forks(s_philo, LOCK);
	set_last_meal_ts(&s_philo->last_meal_ts,
		get_timestamp(s_philo->s_param->starting_tv), s_philo->last_meal_mutx);
	s_philo->meal_eaten++;
	print_msg(s_philo, EAT);
	if (s_philo->s_param->meal_number > 0
		&& s_philo->meal_eaten == s_philo->s_param->meal_number)
		set_bool(&s_philo->full, 1, s_philo->full_mutx);
	frag_usleep(s_philo, s_philo->s_param->time_to_eat);
	handle_forks(s_philo, UNLOCK);
	return (0);
}

// Sleeping routine : prints the msg and usleep
static void	philo_sleep(t_philo *s_philo)
{
	print_msg(s_philo, SLEEP);
	frag_usleep(s_philo, s_philo->s_param->time_to_sleep);
}

// Thinking routine : prints the msg
// If the number of philo is odd, sleep for a short time to ensure fairness
static void	philo_think(t_philo *s_philo)
{
	print_msg(s_philo, THINK);
	if (s_philo->s_param->philo_number % 2 != 0)
		frag_usleep(s_philo, s_philo->s_param->time_to_eat * 2
			- s_philo->s_param->time_to_sleep);
}

// Waits for all pthilo threads to be created then start the simulation loop
// The simulation loop runs while the end signal (bool simulation_end)
// is set to 1
// When the philo reach meal_number of meals eaten, boolean full is set to 1
void	*philo_routine(void *arg)
{
	t_philo	*s_philo;

	s_philo = (t_philo *)arg;
	while (get_bool(&(s_philo->s_param->simulation_ready),
			s_philo->s_param->mutx_ready) == 0)
		usleep(20);
	if (s_philo->number % 2 != 0)
		frag_usleep(s_philo, s_philo->s_param->time_to_eat);
	while (get_bool(&(s_philo->s_param->simulation_end),
			s_philo->s_param->mutx_end) == 0)
	{
		if (get_bool(&(s_philo->full), s_philo->full_mutx) == 1)
			break ;
		if (philo_eat(s_philo) != 0)
			return (NULL);
		philo_sleep(s_philo);
		philo_think(s_philo);
	}
	return (NULL);
}
