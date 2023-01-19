/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/19 12:10:37 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death_routine(void *model_ptr)
{
	t_model	*model;
	int		i;

	i = 0;
	model = (t_model *)model_ptr;
	sem_wait(model->dead_philo);
	while (i < model->params->number_of_philosophers)
	{
		kill(model->pid_list[i], SIGTERM);
		i++;
	}
	free_all(model);
	exit(0);
}

void	check_fed_philos(t_model *model, t_params params)
{
	int	i;

	i = 0;
	while (i < params.number_of_philosophers)
	{
		sem_wait(model->philo_fed);
		i++;
	}
	i = 0;
	while (i < params.number_of_philosophers)
	{
		kill(model->pid_list[i], SIGTERM);
		i++;
	}
}

void	launch_child_processes(t_model *model, t_params params)
{
	int				i;
	t_philosopher	*philosophers;
	pid_t			pid;
	pthread_t		check_death_thread;

	philosophers = (t_philosopher *)model->philosophers;
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_routine(&philosophers[i]);
			free_all(model);
			exit(0);
		}
		else if (pid > 0)
			model->pid_list[i] = pid;
		else
			fork_error();
		i++;
	}
	pthread_create(&check_death_thread, NULL, check_death_routine, model);
	pthread_detach(check_death_thread);
	check_fed_philos(model, params);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_model		model;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (!get_params(&params, argc, argv))
		return (1);
	if (!get_model(&model, &params))
		return (1);
	gettimeofday(&params.simulation_start, NULL);
	populate(&model);
	if (params.number_of_philosophers == 1)
		return (lonely_philo(model.philosophers));
	launch_child_processes(&model, params);
	free_all(&model);
	return (1);
}
