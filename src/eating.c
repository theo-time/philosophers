/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:35 by teliet            #+#    #+#             */
/*   Updated: 2023/01/11 19:11:09 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *this)
{
	struct timeval	current_time;

	// print_action(current_time, this, "is hungry");
	gettimeofday(&current_time, NULL);
	if (this->id % 2 == 0)
	{
		take_fork(this, this->left_fork);
		take_fork(this, this->right_fork);
	}
	else
	{
		take_fork(this, this->right_fork);
		take_fork(this, this->left_fork);
	}
	gettimeofday(&current_time, NULL);
	this->last_meal_time = current_time;
	print_action(current_time, this, "is eating");
	//usleep(this->time_to_eat * 1000);
	//ft_usleep(this, this->time_to_eat);
	//usleep_ms(this->time_to_eat);
	this->nb_meals++;
	this->state = 1;
	// usleep(this->time_to_eat * 1000);
	sleeping(this);
}

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
