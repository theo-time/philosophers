/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:06 by teliet            #+#    #+#             */
/*   Updated: 2023/01/12 14:03:08 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_ended(t_philosopher *this)
{
	int output;

	pthread_mutex_lock(this->die_check_rights);
	output = this->params->dead_philo;
	pthread_mutex_unlock(this->die_check_rights);
	return (output);
}