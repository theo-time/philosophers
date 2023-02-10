/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:56:37 by theo              #+#    #+#             */
/*   Updated: 2023/01/23 16:19:38 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_philo(t_philosopher *this)
{
	int				result;
	struct timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(this->die_check_rights);
	result = this->params->dead_philo;
	pthread_mutex_unlock(this->die_check_rights);
	return (result);
}

void	is_full(t_philosopher *this)
{
	pthread_mutex_lock(this->sim_end_check_rights);
	this->params->fed_philos++;
	pthread_mutex_unlock(this->sim_end_check_rights);
}

int	is_dead(t_philosopher *this)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (this->time_to_die < time_elapsed(this->last_meal_time,
			now));
}

int	simulation_ended(t_philosopher *this)
{
	int	output;

	pthread_mutex_lock(this->sim_end_check_rights);
	output = (this->params->number_of_philosophers == this->params->fed_philos);
	pthread_mutex_unlock(this->sim_end_check_rights);
	return (output);
}
