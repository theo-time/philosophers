/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/02/07 12:11:39 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(struct timeval current_time, t_philosopher *this,
		char *action)
{
	if (check_dead_philo(this))
		return ;
	pthread_mutex_lock(this->print_rights);
	print_timestamp(&current_time, this->params->simulation_start);
	printf(" %d %s\n", this->id, action);
	pthread_mutex_unlock(this->print_rights);
}

void	eating(t_philosopher *this)
{
	struct timeval	current_time;

	if (this->id % 2 == 0)
	{
		take_fork(this, this->right_fork);
		take_fork(this, this->left_fork);
	}
	else
	{
		take_fork(this, this->left_fork);
		take_fork(this, this->right_fork);
	}
	if (is_dead(this))
		dies(this);
	else
	{
		gettimeofday(&current_time, NULL);
		this->last_meal_time = current_time;
		print_action(current_time, this, "is eating");
		this->nb_meals++;
		this->state = 1;
		ft_usleep(this, this->time_to_eat);
	}
	drop_fork(this->left_fork);
	drop_fork(this->right_fork);
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
	if (this->params->number_of_philosophers % 2 == 0 || this->time_to_die >= 2
		* this->time_to_eat + this->time_to_sleep)
		ft_usleep(this, this->time_to_eat - this->time_to_sleep + 1);
	else
		ft_usleep(this, this->time_to_die);
	this->state = 0;
}

void	dies(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "died");
	pthread_mutex_lock(this->die_check_rights);
	this->params->dead_philo = 1;
	pthread_mutex_unlock(this->die_check_rights);
	this->alive = 0;
}
