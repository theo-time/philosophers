/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/05 17:30:50 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philosopher *this, struct timeval current_time)
{
	long int sec_delay = current_time.tv_sec - this->last_meal_time.tv_sec;
	long int usec_delay = current_time.tv_usec - this->last_meal_time.tv_usec;

	return (this->time_to_die < sec_delay * 1000 + usec_delay / 1000);
}

int finished_eating(t_philosopher *this, struct timeval current_time)
{
	long int sec_delay = current_time.tv_sec - this->last_meal_time.tv_sec;
	long int usec_delay = current_time.tv_usec - this->last_meal_time.tv_usec;

	return (this->state == 1 && this->time_to_eat <= sec_delay * 1000 + usec_delay / 1000);
}

int finished_sleeping(t_philosopher *this, struct timeval current_time)
{
	long int sec_delay = current_time.tv_sec - this->last_sleep_time.tv_sec;
	long int usec_delay = current_time.tv_usec - this->last_sleep_time.tv_usec;
	
	return (this->state == 2 && this->time_to_sleep <= sec_delay * 1000 + usec_delay / 1000);
}

int finished_thinking(t_philosopher *this, struct timeval current_time)
{
	long int sec_delay = current_time.tv_sec - this->start_think_time.tv_sec;
	long int usec_delay = current_time.tv_usec - this->start_think_time.tv_usec;
	
	return (this->state == 0 && this->time_to_eat <= sec_delay * 1000 + usec_delay / 1000);
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

void	populate(t_philosopher *philosophers, pthread_mutex_t *forks, t_params params, pthread_mutex_t *print_rights)
{
	int	i;
    struct timeval current_time;
	
	i = 0;
	gettimeofday(&current_time, NULL); 
	while (i < params.number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].alive = 1;
		philosophers[i].state = 0;
		philosophers[i].last_meal_time = current_time;
		philosophers[i].time_to_die = params.time_to_die;
		philosophers[i].time_to_eat = params.time_to_eat;
		philosophers[i].time_to_sleep = params.time_to_sleep;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i+1) % params.number_of_philosophers];
		philosophers[i].print_rights = print_rights;
		i++;
	}
}

t_params	get_params(int argc, char **argv)
{
	t_params params;
	(void)argc;
	params.number_of_philosophers = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);

	return (params);
}

int	main(int argc, char **argv)
{
	pthread_t threads[NUM_PHILOSOPHERS];
	pthread_mutex_t print_rights = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t forks[NUM_PHILOSOPHERS] = PTHREAD_MUTEX_INITIALIZER;
	t_philosopher philosophers[NUM_PHILOSOPHERS];
	t_params params;

	params = get_params(argc, argv);
	populate(philosophers, forks, params, &print_rights);
	for (int i = 0; i < params.number_of_philosophers; ++i)
	{
		pthread_create(&threads[i], NULL, philo_loop, &(philosophers[i]));
	}
	for (int i = 0; i < params.number_of_philosophers; ++i)
	{
		pthread_join(threads[i], NULL);
	}
}