/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/23 18:00:36 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philosopher *this)
{
	if (this->id % 2 == 1)
	{
		print_action(this->params->simulation_start, this, "is thinking");
		ft_usleep(this, this->time_to_eat - 1);
	}
}

void	*philo_loop(void *philosopher)
{
	t_philosopher	*this;

	this = (t_philosopher *)philosopher;
	init_philo(this);
	while (this->alive && !simulation_ended(this) && !(check_dead_philo(this)))
	{		
		if (is_dead(this))
			dies(this);
		if (this->alive && !simulation_ended(this) && !(check_dead_philo(this)))
			eating(this);
		if (this->nb_meals == this->params->eat_before_end)
			is_full(this);
		if (this->alive && !simulation_ended(this) && !(check_dead_philo(this)))
			sleeping(this);
		if (this->alive && !simulation_ended(this) && !(check_dead_philo(this)))
			thinking(this);
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
