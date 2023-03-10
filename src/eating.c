/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:35 by teliet            #+#    #+#             */
/*   Updated: 2023/01/23 17:59:56 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philosopher *this, pthread_mutex_t *fork)
{
	struct timeval	current_time;

	pthread_mutex_lock(fork);
	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "has taken a fork");
}

void	drop_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}
