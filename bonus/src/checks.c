/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:56:37 by theo              #+#    #+#             */
/*   Updated: 2023/02/07 13:03:58 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_full(t_philosopher *this)
{
	sem_post(this->philo_fed);
}

int	is_dead(t_philosopher *this)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (this->time_to_die < time_elapsed(this->last_meal_time,
			now));
}
