/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 13:46:47 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(struct timeval current_time, t_philosopher *this,
		char *action)
{
	// if (simulation_ended(this))
	// 	return ;
	//sem_wait(this->simulation_play);
	if(!this->alive)
		return ;
	//printf(" %d pointer to dead_philo : %p : %d\n", this->id, &(this->params->dead_philo), this->params->dead_philo);
	//sem_post(this->dead_philo);
	sem_wait(this->print_rights);
	print_timestamp(&current_time, *(this->params));
	printf(" %d %s\n", this->id, action);
	sem_post(this->print_rights);
}

void	sleeping(t_philosopher *this)
{
	struct timeval	current_time;

	drop_fork(this);
	drop_fork(this);
	gettimeofday(&current_time, NULL);
	this->last_sleep_time = current_time;
	print_action(current_time, this, "is sleeping");
	this->state = 2;
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
	sem_post(this->dead_philo);
	sem_wait(this->print_rights);
	sem_wait(this->simulation_play);
	usleep(10000);
	//pthread_join(this->wait_thread, NULL);
	// end_of_simulation(this);
}

void	end_of_simulation(t_philosopher *this)
{
	//sem_wait(this->simulation_play);
	//printf(" %d pointer to dead_philo : %p : %d\n", this->id, &(this->params->dead_philo), this->params->dead_philo);
	sem_post(this->dead_philo);
}
