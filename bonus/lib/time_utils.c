/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:58:10 by teliet            #+#    #+#             */
/*   Updated: 2023/02/07 12:11:00 by teliet           ###   ########.fr       */
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
	struct timeval	current_time;

	goal = 0;
	goal = now(this) + time;
	while (now(this) < goal)
	{
		if (is_dead(this))
		{
			dies(this);
			break ;
		}
		usleep(500);
	}
}

void	print_timestamp(struct timeval *tv, t_params params)
{
	long	sec;
	long	ms;
	long	elapsed_time;

	sec = tv->tv_sec - params.simulation_start.tv_sec;
	ms = (tv->tv_usec - params.simulation_start.tv_usec) / 1000;
	elapsed_time = sec * 1000 + ms;
	printf("%ld", elapsed_time);
}
