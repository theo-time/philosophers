/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:22:27 by teliet            #+#    #+#             */
/*   Updated: 2023/02/07 12:23:27 by teliet           ###   ########.fr       */
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
		philosophers[i].philo_fed = model->philo_fed;
		philosophers[i].nb_meals = 0;
		i++;
	}
}

int	get_params(t_params *params, int argc, char **argv)
{
	if (!is_integer(argv[1]) || !is_integer(argv[2]) || !is_integer(argv[3])
		|| !is_integer(argv[4]))
		return (0);
	params->number_of_philosophers = ft_atoi(argv[1]);
	if (params->number_of_philosophers > 200)
		params->number_of_philosophers = 200;
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->dead_philo = 0;
	params->fed_end_mode = 1;
	if (argc == 6)
	{
		if (is_integer(argv[5]))
			params->eat_before_end = ft_atoi(argv[5]);
		else
			return (0);
	}
	else
	{
		params->eat_before_end = -1;
		params->fed_end_mode = 0;
	}
	return (1);
}

sem_t	*ft_sem_open(char *name, int initial_value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, initial_value);
	if (sem == SEM_FAILED)
	{
		sem_unlink(name);
		sem = sem_open(name, O_CREAT, 0644, initial_value);
	}
	return (sem);
}

int	get_model(t_model *model, t_params *params)
{
	t_philosopher	*philosophers;
	sem_t			*forks;

	forks = sem_open("forks", O_CREAT | O_EXCL, 0644,
			params->number_of_philosophers);
	if (forks == SEM_FAILED)
	{
		sem_unlink("forks");
		forks = sem_open("forks", O_CREAT, 0644,
				params->number_of_philosophers);
	}
	model->print_rights = ft_sem_open("print_rights", 1);
	model->dead_philo = ft_sem_open("dead_philo", 0);
	model->philo_fed = ft_sem_open("philo_fed", 0);
	model->forks = forks;
	model->params = params;
	if (!model->philosophers || !model->pid_list)
		return (0);
	return (1);
}
