/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/01/10 17:48:06 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(struct timeval current_time, t_philosopher *this,
		char *action)
{
	if (this->params->dead_philo)
		return ;
	pthread_mutex_lock(this->print_rights);
	print_timestamp(&current_time, *(this->params));
	printf(" %d %s\n", this->id, action);
	pthread_mutex_unlock(this->print_rights);
}

void	sleeping(t_philosopher *this)
{
	struct timeval	current_time;

	drop_fork(this->left_fork);
	// print_action(current_time, this, "dropped left fork");
	drop_fork(this->right_fork);
	// print_action(current_time, this, "dropped right fork");
	gettimeofday(&current_time, NULL);
	this->last_sleep_time = current_time;
	print_action(current_time, this, "is sleeping");
	this->state = 2;
	// usleep(this->time_to_sleep * 1000);
}

void	thinking(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	this->start_think_time = current_time;
	print_action(current_time, this, "is thinking");
	this->state = 0;
}

void	dies(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "died");
	this->alive = 0;
	this->params->dead_philo = 1;
}

void	end_of_simulation(t_philosopher *this)
{
	pthread_mutex_lock(this->die_check_rights);
	this->params->dead_philo = 1;
	pthread_mutex_unlock(this->die_check_rights);
}
