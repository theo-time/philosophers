/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 14:10:54 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*wait_loop(void *philosopher)
{
	t_philosopher	*this;

	this = (t_philosopher *)philosopher;
	//printf("%d waits philo signal\n", this->id);
	sem_wait(this->dead_philo);
	//printf("%d received dead philo signal\n", this->id);
	if(this->alive == 1)
	{
		sem_post(this->dead_philo);
		//printf("%d released dead_philo sem\n", this->id);
		//this->alive = 0;
	}
	else
	{
		//this->alive = 0;
		//printf("%d released dead_philo sem\n", this->id);
		sem_post(this->dead_philo);
		usleep(10000);
		//printf("%d waits dead philo signal again, still holfing print rights\n", this->id);
		sem_wait(this->dead_philo);
		//printf("%d received dead philo signal\n", this->id);

		//free_sems(this->model);
	}
}

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

void 	*philo_routine(void *philosopher)
{
	t_philosopher	*this;
	struct timeval	current_time;
	
	this = (t_philosopher *)philosopher;
	init_philo(this);
	while (this->alive)
	{
		ft_usleep(this, 1);	
		gettimeofday(&current_time, NULL);
		if (check_play(this) && is_dead(this, current_time))
			dies(this);
		else if (check_play(this) && finished_sleeping(this, current_time))
			thinking(this);
		else if (check_play(this) && finished_thinking(this, current_time))
			eating(this);
		if (check_play(this) && this->nb_meals == this->params->eat_before_end)
			end_of_simulation(this);
	}
	return (NULL);
}

void	*philo_loop(t_philosopher *this)
{
	pthread_t loop_thread;

	pthread_create(&loop_thread, NULL, philo_routine, this);
	//pthread_join(loop_thread);
	wait_loop(this);
	pthread_detach(loop_thread);
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

void	launch_child_processes(t_model *model, t_params params)
{
	int				i;
	t_philosopher	*philosophers;
	pid_t			pid;
    // sem_t 			*sem;
	// pthread_t		*dead_philo_thread;
		
	// pthread_create(&this->wait_thread, NULL, wait_loop, &this);
	philosophers = (t_philosopher *)model->philosophers;
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			//printf("pointer to dead_philo : %p : %d",  philosophers[i].params, philosophers[i].params->dead_philo);
			philo_loop(&philosophers[i]);
			//free_this(model);
			//free_sems(model);
			exit(0);
			//free_all(model);
			
		}
		else if (pid > 0)
			model->pid_list[i] = pid;
		else
			fork_error();
		i++;
	}
	i = 0;
	// sem_wait(model->dead_philo);
	// while (i < params.number_of_philosophers)
	// 	kill(model->pid_list[i++], SIGKILL);
	while (i < params.number_of_philosophers)
		waitpid(model->pid_list[i++], NULL, 0);
	free_sems(model);
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
	free_this(&model);
}
