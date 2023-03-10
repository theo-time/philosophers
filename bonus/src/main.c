/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/02/10 18:17:59 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*check_death_routine(void *model_ptr)
// {
// 	t_model	*model;
// 	int		i;

// 	i = 0;
// 	model = (t_model *)model_ptr;
// 	sem_wait(model->dead_philo);
// 	sem_wait(model->print_rights);
// 	while (i < model->params->number_of_philosophers)
// 	{
// 		kill(model->pid_list[i], SIGINT);
// 		i++;
// 	}
// 	free_all(model);
// 	exit(0);
// }

void	*check_fed_philos_routine(void *m)
{
	int	i;
	t_model *model = (t_model *)m;
	i = 0;
	while (i < model->params->number_of_philosophers)
	{
		// printf("MAIN WAITING FOR PHILO\n");
		sem_wait(model->philo_fed);
		i++;
	}
	// printf("ALL PHILO FED, MAIN SENDING MSG\n");
	// sem_wait(model->print_rights);
	sem_post(model->simulation_ended);
	// i = 0;
	// while (i < params.number_of_philosophers)
	// {
	// 	kill(model->pid_list[i], SIGINT);
	// 	i++;
	// }
}

void	launch_child_processes(t_model *model, t_params params)
{
	int				i;
	int				status;
	t_philosopher	*philosophers;
	pid_t			pid;
	pthread_t		check_fed_philos_thread;

	philosophers = (t_philosopher *)model->philosophers;
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_routine(&philosophers[i]);
			free_all(model);
			free(philosophers[i].wait_mutex);
			exit(0);
		}
		else if (pid > 0)
			model->pid_list[i] = pid;
		else
			fork_error();
		i++;
	}
	pthread_create(&check_fed_philos_thread, NULL, check_fed_philos_routine, model);
	pthread_detach(check_fed_philos_thread);
	i = 0;
	while (i < params.number_of_philosophers)
	{
		// printf("main waiting process %d\n", i);
		waitpid(model->pid_list[i], &status, 0);
		// printf("main recoverd process %d\n", i);
		i++;
	}
	// check_fed_philos(model, params);
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
