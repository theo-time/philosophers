/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:58:10 by teliet            #+#    #+#             */
/*   Updated: 2023/02/07 12:11:20 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now(t_philosopher *this)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (time_elapsed(this->params->simulation_start, tv));
}

void	ft_usleep(t_philosopher *this, time_t time)
{
	time_t			goal;
	struct timeval	tv;

	goal = 0;
	goal = now(this) + time;
	while (now(this) < goal)
	{
		if (simulation_ended(this) || check_dead_philo(this))
			break ;
		if (is_dead(this))
		{
			gettimeofday(&tv, NULL);
			dies(this);
			break ;
		}
		usleep(500);
	}
}

void	print_timestamp(struct timeval *tv, struct timeval simulation_start)
{
	long	sec;
	long	ms;
	long	elapsed_time;

	sec = tv->tv_sec - simulation_start.tv_sec;
	ms = (tv->tv_usec - simulation_start.tv_usec) / 1000;
	elapsed_time = sec * 1000 + ms;
	printf("%ld", elapsed_time);
}
