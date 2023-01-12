/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/12 14:19:51 by teliet           ###   ########.fr       */
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
	init_philo(this);
	while (this->alive)
	{
		ft_usleep(this, 1);
		if (simulation_ended(this))
			break ;
		gettimeofday(&current_time, NULL);
		if (is_dead(this, current_time))
			dies(this);	
		if (finished_sleeping(this, current_time))
			thinking(this);
		else if (finished_thinking(this, current_time))
			eating(this);
		if (this->nb_meals == this->params->eat_before_end)
			end_of_simulation(this);
		// ft_usleep(this, 1);
		// gettimeofday(&current_time, NULL);
		// if (is_dead(this, current_time))
		// 	dies(this);
		// if (finished_sleeping(this, current_time))
		// 	thinking(this);
		// else if (finished_thinking(this, current_time))
		// 	eating(this);
		// if (this->nb_meals == this->params->eat_before_end)
		// 	end_of_simulation(this);
		// if (simulation_ended(this))
		// 	break ;
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

void	launch_threads(t_model *model, t_params params)
{
	int				i;
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)model->philosophers;
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pthread_create(&model->threads[i], NULL, philo_loop,
			&(philosophers[i]));
		i++;
	}
	i = 0;
	while (i < params.number_of_philosophers)
	{
		pthread_join(model->threads[i], NULL);
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
	launch_threads(&model, params);
	free_all(&model);
}
