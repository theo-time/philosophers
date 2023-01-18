/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:33:10 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 13:50:35 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_elapsed(struct timeval start_time, struct timeval now)
{
	return ((now.tv_sec - start_time.tv_sec) * 1000 + (now.tv_usec
			- start_time.tv_usec) / 1000);
}

int	is_dead(t_philosopher *this, struct timeval now)
{
	check_play(this);
	gettimeofday(&now, NULL);
	return (this->time_to_die < time_elapsed(this->last_meal_time,
			now));
}

int	finished_eating(t_philosopher *this, struct timeval now)
{
	check_play(this);
	gettimeofday(&now, NULL);
	return (this->state == 1
		&& this->time_to_eat <= time_elapsed(this->last_meal_time, now));
}

int	finished_sleeping(t_philosopher *this, struct timeval now)
{
	check_play(this);
	gettimeofday(&now, NULL);
	return (this->state == 2
		&& this->time_to_sleep <= time_elapsed(this->last_sleep_time, now));
}

int	finished_thinking(t_philosopher *this, struct timeval now)
{
	check_play(this);
	gettimeofday(&now, NULL);
	return (this->state == 0 && (this->time_to_eat - this->time_to_sleep)
		+ 1 <= time_elapsed(this->start_think_time, now));
}
