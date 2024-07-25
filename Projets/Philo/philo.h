/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:29:02 by tlebon            #+#    #+#             */
/*   Updated: 2024/07/25 21:09:37 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>		// for memset
#include <stdio.h>		// for printf
#include <stdlib.h>		// for malloc
#include <unistd.h>		// for write usleep
#include <sys/time.h>	// for gettimeofday
#include <pthread.h>	// for pthread functions

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int	*infos_tab;
	
}t_philo;


#endif