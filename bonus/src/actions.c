/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/02/10 18:21:56 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(struct timeval current_time, t_philosopher *this,
		char *action)
{
	if (!is_alive(this))
		return ;
	sem_wait(this->print_rights);
	print_timestamp(&current_time, *(this->params));
	printf(" %d %s\n", this->id, action);
	sem_post(this->print_rights);
}

void	eating(t_philosopher *this)
{
	struct timeval	current_time;

	take_fork(this);
	take_fork(this);
	if (is_dead(this))
	{
		dies(this);
		return ;
	}
	gettimeofday(&current_time, NULL);
	this->last_meal_time = current_time;
	print_action(current_time, this, "is eating");
	this->nb_meals++;
	this->state = 1;
	ft_usleep(this, this->time_to_eat);
	drop_fork(this);
	drop_fork(this);
}

void	sleeping(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	this->last_sleep_time = current_time;
	print_action(current_time, this, "is sleeping");
	ft_usleep(this, this->time_to_sleep);
	this->state = 2;
}

void	thinking(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	this->start_think_time = current_time;
	print_action(current_time, this, "is thinking");
	ft_usleep(this, this->time_to_eat - this->time_to_sleep + 1);
	this->state = 0;
}

void	dies(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(this->wait_mutex);
	this->alive = 0;
	pthread_mutex_unlock(this->wait_mutex);
	sem_post(this->simulation_ended);
}
