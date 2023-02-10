/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:03:42 by theo              #+#    #+#             */
/*   Updated: 2023/02/10 18:26:16 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*wait_thread_routine(void *philo)
{
	t_philosopher *this = (t_philosopher *)philo;
	sem_wait(this->simulation_ended);
	// printf("PHILO RECEIVED DEATH SIGNAL\n");
	pthread_mutex_lock(this->wait_mutex);
	this->alive = 0;
	pthread_mutex_unlock(this->wait_mutex);
	sem_post(this->simulation_ended);
}

int	init_philo(t_philosopher *this)
{
	this->wait_mutex = malloc(sizeof(pthread_mutex_t));
	if(!this->wait_mutex)
		return 0;
	if (pthread_mutex_init(this->wait_mutex, NULL) != 0)
	{
		printf("pthread_mutex_init fail");
		return 0;
	}
	pthread_create(&this->wait_thread, NULL, wait_thread_routine, this);
	pthread_detach(this->wait_thread);
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
	while (is_alive(this))
	{
		if (is_alive(this))
			eating(this);
		if (is_alive(this) && is_full(this))
			sem_post(this->philo_fed);
		if (is_alive(this))
			sleeping(this);
		if (is_alive(this))
			thinking(this);
	}
	// printf("out of loop\n");
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
