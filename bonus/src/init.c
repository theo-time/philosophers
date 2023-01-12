/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:22:27 by teliet            #+#    #+#             */
/*   Updated: 2023/01/12 17:28:23 by teliet           ###   ########.fr       */
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
		philosophers[i].forks = model->forks;
		philosophers[i].print_rights = model->print_rights;
		philosophers[i].params = model->params;
		philosophers[i].dead_philo = model->dead_philo;
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

int	get_model(t_model *model, t_params *params)
{
	t_philosopher	*philosophers;
	sem_t			*forks;

	forks = sem_open("forks", O_CREAT | O_EXCL, 0644,
			params->number_of_philosophers);
	if (forks == SEM_FAILED)
	{
		sem_close(forks);
		sem_unlink("forks");
		forks = sem_open("forks", O_CREAT, 0644,
				params->number_of_philosophers);
	}
	model->pid_list = malloc(sizeof(pid_t) * params->number_of_philosophers);
	model->print_rights = sem_open("print_rights", O_CREAT, 0644, 1);
	model->dead_philo = sem_open("dead_philo", O_CREAT, 0644, 1);
	philosophers = malloc(params->number_of_philosophers
			* sizeof(t_philosopher));
	model->forks = forks;
	model->philosophers = philosophers;
	model->params = params;
	if (!philosophers || !model->pid_list)
		return (0);
	return (1);
}
