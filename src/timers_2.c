/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:06 by teliet            #+#    #+#             */
/*   Updated: 2023/01/12 18:12:00 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_ended(t_philosopher *this)
{
	int	output;

	pthread_mutex_lock(this->sim_end_check_rights);
    //printf("%d\n",  this->params->fed_philos);
	output = (this->params->number_of_philosophers == this->params->fed_philos);
	pthread_mutex_unlock(this->sim_end_check_rights);
	return (output);
}
