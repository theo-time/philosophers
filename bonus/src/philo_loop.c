/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:03:42 by theo              #+#    #+#             */
/*   Updated: 2023/01/23 17:18:12 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philosopher *this)
{
	if (this->id % 2 == 1)
	{
		thinking(this);
		ft_usleep(this, this->time_to_eat - 1);
	}
}

void	*philo_routine(void *philosopher)
{
	t_philosopher	*this;
	struct timeval	current_time;

	this = (t_philosopher *)philosopher;
	init_philo(this);
	while (this->alive)
	{
		if (this->alive)
			eating(this);
		if (this->nb_meals == this->params->eat_before_end)
			is_full(this);
		if (this->alive)
			sleeping(this);
		if (this->alive)
			thinking(this);
	}
	return (NULL);
}

int	lonely_philo(t_philosopher *philosophers)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	print_action(current_time, &philosophers[0], " is thinking");
	print_action(current_time, &philosophers[0], " has taken a fork");
	usleep(philosophers[0].time_to_die * 1000);
	gettimeofday(&current_time, NULL);
	print_action(current_time, &philosophers[0], " died");
	return (0);
}
