/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:00:06 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 14:05:05 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_play(t_philosopher *this)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	// print_action(current_time, this, "is waiting for sim_play");
    sem_wait(this->simulation_play);
    sem_post(this->simulation_play);  
	// print_action(current_time, this, "released sim_play");
    return (1);
}

// int	simulation_ended(t_philosopher *this)
// {
// 	int	output;

// 	sem_wait(this->simulation_play);
// 	output = this->params->dead_philo;
// 	sem_post(this->simulation_play);
// 	//printf("%d pointer to dead_philo : %p : %d\n", this->id,  &(this->params->dead_philo), this->params->dead_philo);
// 	return (output);
// }
