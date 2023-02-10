/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:56:37 by theo              #+#    #+#             */
/*   Updated: 2023/02/10 18:25:19 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philosopher *this)
{
	// printf("%d is full\n" , this->id);
	// this->alive = 0;
	// sem_post(this->philo_fed);
	// if(this->id % 2 == 1)
	// 	return(this->nb_meals == this->params->eat_before_end );
	// if(this->id % 2 == 0)
	return(this->nb_meals == this->params->eat_before_end );
}

int	is_dead(t_philosopher *this)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (this->time_to_die < time_elapsed(this->last_meal_time,
			now));
}

int	is_alive(t_philosopher *this)
{
	int result;
	pthread_mutex_lock(this->wait_mutex);
	result = this->alive;
	pthread_mutex_unlock(this->wait_mutex);
	return result;
}
