/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:22:27 by teliet            #+#    #+#             */
/*   Updated: 2023/01/12 18:20:33 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	populate(t_model *model)
{
	int				i;
	t_philosopher	*philosophers;

	i = 0;
	philosophers = (t_philosopher *)model->philosophers;
	while (i < model->params->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].alive = 1;
		philosophers[i].state = 0;
		philosophers[i].last_meal_time = model->params->simulation_start;
		philosophers[i].time_to_die = model->params->time_to_die;
		philosophers[i].time_to_eat = model->params->time_to_eat;
		philosophers[i].time_to_sleep = model->params->time_to_sleep;
		philosophers[i].left_fork = &model->forks[i];
		philosophers[i].right_fork = &model->forks[(i + 1)
			% model->params->number_of_philosophers];
		philosophers[i].print_rights = model->print_rights;
		philosophers[i].sim_end_check_rights = model->sim_end_check_rights;
		philosophers[i].params = model->params;
		philosophers[i].die_check_rights = model->die_check_rights;
		philosophers[i].nb_meals = 0;
		i++;
	}
	model->philosophers = philosophers;
}

int	get_params(t_params *params, int argc, char **argv)
{
	if (!is_integer(argv[1]) || !is_integer(argv[2]) || !is_integer(argv[3])
		|| !is_integer(argv[4]))
		return (0);
	params->number_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->dead_philo = 0;
	params->fed_philos = 0;
	if (argc == 6)
	{
		if (is_integer(argv[5]))
			params->eat_before_end = ft_atoi(argv[5]);
		else
			return (0);
	}
	else
		params->eat_before_end = -1;
	return (1);
}

int	init_forks(t_model *model)
{
	int	i;

	i = 0;
	while (i < model->params->number_of_philosophers)
	{
		if (pthread_mutex_init(&(model->forks[i]), NULL) != 0)
		{
			printf("pthread_mutex_init");
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_model(t_model *model, t_params *params)
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;

	threads = malloc(params->number_of_philosophers * sizeof(pthread_t));
	forks = malloc(params->number_of_philosophers * sizeof(pthread_mutex_t));
	philosophers = malloc(params->number_of_philosophers
			* sizeof(t_philosopher));
	model->threads = threads;
	model->forks = forks;
	model->philosophers = philosophers;
	model->print_rights = malloc(sizeof(pthread_mutex_t));
	model->die_check_rights = malloc(sizeof(pthread_mutex_t));
	model->sim_end_check_rights = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(model->sim_end_check_rights, NULL);
	pthread_mutex_init(model->print_rights, NULL);
	pthread_mutex_init(model->die_check_rights, NULL);
	model->params = params;
	init_forks(model);
	if (!threads || !forks || !philosophers)
		return (0);
	return (1);
}
