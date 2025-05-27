/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:34:24 by tlebon            #+#    #+#             */
/*   Updated: 2024/09/24 17:22:04 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// Basic atoi
int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;

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

// Sleeps a very short period of time then check is the simulation has ended
// The cycle goes on until [value] time has elapsed
void	frag_usleep(t_philo *s_philo, int value)
{
	time_t	start;

	start = get_timestamp(s_philo->s_param->starting_tv);
	while (get_timestamp(s_philo->s_param->starting_tv) - start < value)
	{
		if (get_bool(&s_philo->s_param->simulation_end,
				s_philo->s_param->mutx_end) == 1)
			return ;
		usleep(10);
	}
}

// Prints a message according to status
void	print_msg(t_philo *s_philo, t_msg status)
{
	int				*end_bool;
	pthread_mutex_t	*mutex;

	end_bool = &(s_philo->s_param->simulation_end);
	mutex = s_philo->s_param->mutx_end;
	pthread_mutex_lock(s_philo->s_param->mutx_write);
	if (status == FORK && get_bool(end_bool, mutex) == 0)
		printf("%li %i has taken a fork\n",
			get_timestamp(s_philo->s_param->starting_tv), s_philo->number);
	else if (status == EAT && get_bool(end_bool, mutex) == 0)
		printf("%li %i is eating\n",
			get_timestamp(s_philo->s_param->starting_tv), s_philo->number);
	else if (status == SLEEP && get_bool(end_bool, mutex) == 0)
		printf("%li %i is sleeping\n",
			get_timestamp(s_philo->s_param->starting_tv), s_philo->number);
	else if (status == THINK && get_bool(end_bool, mutex) == 0)
		printf("%li %i is thinking\n",
			get_timestamp(s_philo->s_param->starting_tv), s_philo->number);
	else if (status == DIE)
		printf("%li %i died\n",
			get_timestamp(s_philo->s_param->starting_tv), s_philo->number);
	pthread_mutex_unlock(s_philo->s_param->mutx_write);
	return ;
}
