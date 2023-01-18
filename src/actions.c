/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 11:31:13 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_philo(t_philosopher *this)
{
	int result; 

	pthread_mutex_lock(this->die_check_rights);
	result = this->params->dead_philo;
	pthread_mutex_unlock(this->die_check_rights);
	return(result);
}

void	print_action(struct timeval current_time, t_philosopher *this,
		char *action)
{	
	if (check_dead_philo(this))
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
	drop_fork(this->right_fork);
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
	pthread_mutex_lock(this->die_check_rights);
	this->params->dead_philo = 1;
	pthread_mutex_unlock(this->die_check_rights);
	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "going to sleep\n");
	usleep(1000000000);
	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "finished usleep\n");
}

void	is_full(t_philosopher *this)
{
	pthread_mutex_lock(this->sim_end_check_rights);
	this->params->fed_philos++;
    // printf("%d\n",  this->params->fed_philos);
	pthread_mutex_unlock(this->sim_end_check_rights);
	this->alive = 0;
	// exit(0);
}
