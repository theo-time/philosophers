/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/01/04 18:41:57 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philosopher	*this)
{
  	struct timeval current_time;
    take_fork(this, this->left_fork);
    take_fork(this, this->right_fork);
	gettimeofday(&current_time, NULL);  
    printf("%ld %d is eating\n", current_time.tv_sec, this->id);
    this->state = 1;
	this->last_meal_time = current_time.tv_sec;
    // usleep(this->time_to_eat * 1000); 
}

void sleeping(t_philosopher	*this)
{
    drop_fork(this->left_fork);
    drop_fork(this->right_fork);
  	struct timeval current_time;
	gettimeofday(&current_time, NULL);  
    printf("%ld %d is sleeping\n", current_time.tv_sec, this->id);
    this->state = 2;
	this->last_sleep_time = current_time.tv_sec;
    // usleep(this->time_to_sleep * 1000);  
}

void thinking(t_philosopher	*this)
{
  	struct timeval current_time;
	gettimeofday(&current_time, NULL);  
    printf("%ld %d is thinking\n", current_time.tv_sec, this->id);
	this->start_think_time = current_time.tv_sec;
    this->state = 0;
}

void take_fork(t_philosopher *this, pthread_mutex_t *fork)
{
  	struct timeval current_time;
    pthread_mutex_lock(fork);
	gettimeofday(&current_time, NULL);
    printf("%ld %d has taken a fork\n", current_time.tv_sec, this->id);
}

void drop_fork(pthread_mutex_t *fork)
{
    pthread_mutex_unlock(fork);
}

void dies(t_philosopher *this)
{
  	struct timeval current_time;
	gettimeofday(&current_time, NULL);
    printf("%ld %d died\n", current_time.tv_sec, this->id);
    this->alive = 0;
    //exit(1);
}