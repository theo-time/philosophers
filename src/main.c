/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/06 18:44:55 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int time_elapsed(struct timeval current_time)
// {
// 	static int init = 0;
// 	static struct timeval start_time;
	
// 	if(!init)
// 	{
// 		gettimeofday(&start_time, NULL); 
// 		init = 1;
// 	}
// 	//printf("%ld\n", (current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_usec - start_time.tv_usec) / 1000);
// 	return ((current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_usec - start_time.tv_usec) / 1000);
// }


int time_elapsed(struct timeval start_time, struct timeval current_time)
{
	return ((current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_usec - start_time.tv_usec) / 1000);
}

int is_dead(t_philosopher *this, struct timeval current_time)
{
	return (this->time_to_die < time_elapsed(this->last_meal_time, current_time));
}

int finished_eating(t_philosopher *this, struct timeval current_time)
{
	return (this->state == 1 && this->time_to_eat <= time_elapsed(this->last_meal_time, current_time));
}

int finished_sleeping(t_philosopher *this, struct timeval current_time)
{
	return (this->state == 2 && this->time_to_sleep <= time_elapsed(this->last_sleep_time, current_time));
}

int finished_thinking(t_philosopher *this, struct timeval current_time)
{
	return (this->state == 0 && 3 <= time_elapsed(this->start_think_time, current_time));
}

void		usleep_ms(int ms)
{
	ms = ms * 10;
	while(ms)
	{
		usleep(100);
		ms--;
	}
}

void	*philo_loop(void *philosopher)
{
	t_philosopher	*this;
    struct timeval current_time;
	this = (t_philosopher *)philosopher;
	gettimeofday(&current_time, NULL); 
    // print_action(current_time, this, "is born");
	// eating(this);
	if(this->id % 2 == 0)
		eating(this);
	else 
	{
		usleep_ms(1);
		thinking(this);
	}
   // print_action(current_time, this, "is born");
	while (this->alive)
	{
		// usleep(1000000);
		gettimeofday(&current_time, NULL); 
		// printf("%d\n", time_elapsed(current_time));
		if(finished_eating(this,current_time))
			sleeping(this);
		else if(finished_sleeping(this,current_time))
			thinking(this);
		else if(finished_thinking(this,current_time))
			eating(this);
		else if(is_dead(this, current_time)) 
			dies(this);
		else if(this->nb_meals == this->params.eat_before_end) 
			exit(1);
	}
	return (0);
}

void	populate(t_philosopher *philosophers, pthread_mutex_t *forks, t_params params, pthread_mutex_t *print_rights)
{
	int	i;
    struct timeval current_time;
	
	i = 0;
	gettimeofday(&current_time, NULL); 
	// time_elapsed(current_time);
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
		philosophers[i].params = params;
		philosophers[i].nb_meals = 0;
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
	if(argc == 6)
		params.eat_before_end = ft_atoi(argv[5]);
	else 
		params.eat_before_end = -1;
	return (params);
}

int	main(int argc, char **argv)
{
	int i;
	pthread_t threads[NUM_PHILOSOPHERS];
	pthread_mutex_t print_rights = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t forks[NUM_PHILOSOPHERS] = PTHREAD_MUTEX_INITIALIZER;
	t_philosopher philosophers[NUM_PHILOSOPHERS];
	t_params params;
	if(!(argc == 5 || argc == 6))
		return(1);
	params = get_params(argc, argv);
	gettimeofday(&params.simulation_start, NULL);
	populate(philosophers, forks, params, &print_rights);
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, philo_loop, &(philosophers[i]));
		i += 2;
	}
	i = 1;
	while (i < params.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, philo_loop, &(philosophers[i]));
		i += 2;
	}
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}