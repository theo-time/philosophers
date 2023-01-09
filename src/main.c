/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/09 19:12:42 by teliet           ###   ########.fr       */
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
	gettimeofday(&current_time, NULL); 
    // print_action(current_time, this, "check death");
	return (this->time_to_die < time_elapsed(this->last_meal_time, current_time));
}

int finished_eating(t_philosopher *this, struct timeval current_time)
{
	gettimeofday(&current_time, NULL); 
	return (this->state == 1 && this->time_to_eat <= time_elapsed(this->last_meal_time, current_time));
}

int finished_sleeping(t_philosopher *this, struct timeval current_time)
{
	gettimeofday(&current_time, NULL); 
	return (this->state == 2 && this->time_to_sleep <= time_elapsed(this->last_sleep_time, current_time));
}

int finished_thinking(t_philosopher *this, struct timeval current_time)
{
	gettimeofday(&current_time, NULL); 
	return (this->state == 0 && (this->time_to_eat - this->time_to_sleep) + 1 <= time_elapsed(this->start_think_time, current_time));
}


void	*philo_loop(void *philosopher)
{
	t_philosopher	*this;
    struct timeval current_time;
	this = (t_philosopher *)philosopher;
    // print_action(current_time, this, "is born");
	// eating(this);
	if(this->id % 2 == 0)
		eating(this);
	else 
	{
		usleep(2000);
		thinking(this);
	}
   // print_action(current_time, this, "is born");
	while (this->alive)
	{
		if(this->params->dead_philo) 
			break ;
		// usleep(1000000);
		// printf("%d\n", time_elapsed(current_time));
		// if(finished_eating(this,current_time))
		// 	sleeping(this);
		if(finished_sleeping(this,current_time))
			thinking(this);
		else if(finished_thinking(this,current_time))
			eating(this);

		ft_usleep(this, 1);
		// if(this->nb_meals == this->params->eat_before_end) 
		// 	exit(1);
		// gettimeofday(&current_time, NULL); 
		if(is_dead(this, current_time)) 
			dies(this);
	}
	return (0);
}

void	populate(t_philosopher *philosophers, pthread_mutex_t *forks, t_params *params, pthread_mutex_t *print_rights, pthread_mutex_t *die_check_rights)
{
	int	i;
    struct timeval current_time;
	
	i = 0;
	gettimeofday(&current_time, NULL); 
	// time_elapsed(current_time);
	while (i < params->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].alive = 1;
		philosophers[i].state = 0;
		philosophers[i].last_meal_time = current_time;
		philosophers[i].time_to_die = params->time_to_die;
		philosophers[i].time_to_eat = params->time_to_eat;
		philosophers[i].time_to_sleep = params->time_to_sleep;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i+1) % params->number_of_philosophers];
		philosophers[i].print_rights = print_rights;
		philosophers[i].params = params;
		philosophers[i].die_check_rights = die_check_rights;
		// philosophers[i].model = model;
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
	params.dead_philo = 0;
	if(argc == 6)
		params.eat_before_end = ft_atoi(argv[5]);
	else 
		params.eat_before_end = -1;
	return (params);
}


// t_model	get_model(pthread_t *threads , pthread_mutex_t *print_rights, pthread_mutex_t *forks, void *philosophers)
// {
// 	t_model model;
// 	model.threads = threads;
// 	model.print_rights = print_rights;
// 	model.forks = forks;
// 	model.philosophers = philosophers;
// 	return (model);
// }

void lonely_philo(t_philosopher *philosophers)
{
    struct timeval current_time;
	gettimeofday(&current_time, NULL);
	print_action(current_time, &philosophers[0], " is thinking");
	print_action(current_time, &philosophers[0], " has taken a fork");
	usleep(philosophers[0].time_to_die * 1000);
	gettimeofday(&current_time, NULL);
	print_action(current_time, &philosophers[0], " died");
}

void free_all(pthread_t *threads,pthread_mutex_t *print_rights, pthread_mutex_t *forks, t_philosopher *philosophers, int nb_philosophers)
{
	int i;
	(void)threads;

	i = 0;
	while(i < nb_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(print_rights);
	free(philosophers);
	free(threads);
	free(forks);
}

int	main(int argc, char **argv)
{
	int i;
	pthread_t *threads;
	pthread_mutex_t print_rights = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t die_check_rights = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t *forks;
	t_philosopher *philosophers;
	t_params params;
	// t_model model;

	i = 0;

	if(!(argc == 5 || argc == 6))
		return(1);
	params = get_params(argc, argv);
	threads = malloc(params.number_of_philosophers * sizeof(pthread_t));
	forks = malloc(params.number_of_philosophers * sizeof(pthread_mutex_t));
	philosophers = malloc(params.number_of_philosophers * sizeof(t_philosopher));
	while(i < params.number_of_philosophers)
	{
  		if (pthread_mutex_init(&forks[i], NULL) != 0) {
            perror("pthread_mutex_init");
            return 1;
        }
		i++;
	}
	// model = get_model(threads, &print_rights, forks, philosophers);
	
	gettimeofday(&params.simulation_start, NULL);
	populate(philosophers, forks, &params, &print_rights, &die_check_rights);
	if(params.number_of_philosophers == 1)
	{
		lonely_philo(philosophers);
		return(1);
	}
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pthread_create(&threads[i], NULL, philo_loop, &(philosophers[i]));
		i++;
	}
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	free_all(threads, &print_rights, forks, philosophers, params.number_of_philosophers);
}