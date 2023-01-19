/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:03:42 by theo              #+#    #+#             */
/*   Updated: 2023/01/19 12:09:57 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philosopher *this)
{
	if (this->id % 2 == 0)
		eating(this);
	else
	{
		thinking(this);
		ft_usleep(this, this->params->time_to_eat - 1);
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
		ft_usleep(this, 1);
		gettimeofday(&current_time, NULL);
		if (is_dead(this, current_time))
			dies(this);
		else if (finished_sleeping(this, current_time))
			thinking(this);
		else if (finished_thinking(this, current_time))
			eating(this);
		if (this->nb_meals >= this->params->eat_before_end
			&& this->params->fed_end_mode)
			sem_post(this->philo_fed);
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
