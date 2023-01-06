/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:26:31 by teliet            #+#    #+#             */
/*   Updated: 2023/01/06 18:43:53 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_action(struct timeval current_time, t_philosopher *this, char *action)
{
    pthread_mutex_lock(this->print_rights);
    print_timestamp(&current_time, this->params);
    printf(" %d %s\n", this->id, action);
    pthread_mutex_unlock(this->print_rights);
}

void eating(t_philosopher	*this)
{
  	struct timeval current_time;
    // print_action(current_time, this, "is hungry");
    gettimeofday(&current_time, NULL);
    if(this->id % 2 == 0)
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
    usleep(this->time_to_eat * 1000);
    //usleep_ms(this->time_to_eat);
    this->nb_meals++;
    this->state = 1;
    // usleep(this->time_to_eat * 1000);
    sleeping(this);
}

void sleeping(t_philosopher	*this)
{
  	struct timeval current_time;
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

void thinking(t_philosopher	*this)
{
  	struct timeval current_time;
	gettimeofday(&current_time, NULL);  
	this->start_think_time = current_time;
    print_action(current_time, this, "is thinking");
    this->state = 0;
}

void take_fork(t_philosopher *this, pthread_mutex_t *fork)
{
  	struct timeval current_time;
    pthread_mutex_lock(fork);
	gettimeofday(&current_time, NULL);  
    print_action(current_time, this, "has taken a fork");
}

void drop_fork(pthread_mutex_t *fork)
{
    pthread_mutex_unlock(fork);
}

void dies(t_philosopher *this)
{
  	struct timeval current_time;
	gettimeofday(&current_time, NULL);  
    print_action(current_time, this, "died");
    this->alive = 0;
    exit(1);
}