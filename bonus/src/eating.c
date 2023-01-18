/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:35 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 14:09:16 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	take_fork(this);
	take_fork(this);
	gettimeofday(&current_time, NULL);
	this->last_meal_time = current_time;
	print_action(current_time, this, "is eating");
	ft_usleep(this, this->time_to_eat);
	if(check_play(this))
	{
		this->nb_meals++;
		this->state = 1;
	}
	sleeping(this);
}

void	take_fork(t_philosopher *this)
{
	struct timeval	current_time;

	sem_wait(this->forks);
	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "has taken a fork");
}

void	drop_fork(t_philosopher *this)
{
	sem_post(this->forks);
}
