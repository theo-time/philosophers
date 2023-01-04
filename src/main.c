/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/04 18:41:06 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philosopher *this, struct timeval current_time)
{
	return (this->time_to_die < current_time.tv_sec - this->last_meal_time);
}

int finished_eating(t_philosopher *this, struct timeval current_time)
{
	return (this->state == 1 && this->time_to_eat <= current_time.tv_sec - this->last_meal_time);
}

int finished_sleeping(t_philosopher *this, struct timeval current_time)
{
	return (this->state == 2 && this->time_to_sleep <= current_time.tv_sec - this->last_sleep_time);
}

int finished_thinking(t_philosopher *this, struct timeval current_time)
{
	return (this->state == 0 && this->time_to_eat <= current_time.tv_sec - this->start_think_time);
}

void	*philo_loop(void *philosopher)
{
	t_philosopher	*this;
    struct timeval current_time;
	this = (t_philosopher *)philosopher;
	if(this->id % 2 == 0)
		eating(this);
	else
		thinking(this);
	while (this->alive)
	{
		gettimeofday(&current_time, NULL); 
		if(is_dead(this, current_time)) 
			dies(this);
		else if(finished_eating(this,current_time))
			sleeping(this);
		else if(finished_sleeping(this,current_time))
			thinking(this);
		else if(finished_thinking(this,current_time))
			eating(this);
	}
	return (0);
}

void	populate(t_philosopher *philosophers, pthread_mutex_t *forks)
{
	int	i;
    struct timeval current_time;
	
	i = 0;
	gettimeofday(&current_time, NULL); 
	while (i < NUM_PHILOSOPHERS)
	{
		philosophers[i].id = i + 1;
		philosophers[i].alive = 1;
		philosophers[i].state = 0;
		philosophers[i].last_meal_time = current_time.tv_sec;
		philosophers[i].time_to_die = 3;
		philosophers[i].time_to_eat = 1;
		philosophers[i].time_to_sleep = 1;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i+1) % NUM_PHILOSOPHERS];
		i++;
	}
}

int	main(void)
{
	pthread_t threads[NUM_PHILOSOPHERS];
	pthread_mutex_t forks[NUM_PHILOSOPHERS] = PTHREAD_MUTEX_INITIALIZER;
	t_philosopher philosophers[NUM_PHILOSOPHERS];

	populate(philosophers, forks);
	for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
	{
		pthread_create(&threads[i], NULL, philo_loop, &(philosophers[i]));
	}

	for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
}