/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:56:37 by theo              #+#    #+#             */
/*   Updated: 2023/01/19 11:57:09 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_philo(t_philosopher *this)
{
	int	result;

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
