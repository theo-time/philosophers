/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/11 19:04:49 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philosopher *this)
{
	if (this->id % 2 == 0)
		eating(this);
	else
	{
		thinking(this);
		ft_usleep(this, this->params->time_to_eat - 1);
	}
}

void	*philo_loop(void *philosopher)
{
	t_philosopher	*this;
	struct timeval	current_time;

 
	this = (t_philosopher *)philosopher;
    //printf("Hello world from child %d\n", this->id);
	init_philo(this);
	while (this->alive)
	{
		if (this->params->dead_philo)
			break ;
		if (finished_sleeping(this, current_time))
			thinking(this);
		else if (finished_thinking(this, current_time))
			eating(this);
		ft_usleep(this, 1);
		if (this->nb_meals == this->params->eat_before_end)
			end_of_simulation(this);
		gettimeofday(&current_time, NULL);
		if (is_dead(this, current_time))
			dies(this);
	}
	return (NULL);
}

int	lonely_philo(t_philosopher *philosophers)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	print_action(current_time, &philosophers[0], " is thinking");
	print_action(current_time, &philosophers[0], " has taken a fork");
	usleep(philosophers[0].time_to_die * 1000);
	gettimeofday(&current_time, NULL);
	print_action(current_time, &philosophers[0], " died");
	return (0);
}

void	launch_child(t_model *model, t_params params, t_philosopher this)
{
	
}

void	launch_child_processes(t_model *model, t_params params)
{
	int				i;
	t_philosopher	*philosophers;
	t_philosopher	this;
    pid_t pid;
    pid_t *pid_list;
	
	pid_list = malloc(sizeof(pid_t) * params.number_of_philosophers);
	philosophers = (t_philosopher *)model->philosophers;
	i = 0;
	while (i < params.number_of_philosophers)
	{
		this = philosophers[i];
        pid = fork();
        if (pid == 0) {
            // child process
			philo_loop(&this);
			free_all(model);
			exit(0);
        } else if (pid > 0) {
			pid_list[i] = pid;
            // parent process
            // wait for child to finish before continuing
           // waitpid(pid, NULL, 0);
        } else {
            // fork error
            printf("Fork failed");
            exit(1);
        }
		i++;
	}
	i = 0;
	while (i < params.number_of_philosophers)
	{
		waitpid(pid_list[i], NULL, 0);
		i++;
	}
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
}
