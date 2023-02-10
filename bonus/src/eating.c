/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:39:35 by teliet            #+#    #+#             */
/*   Updated: 2023/01/23 18:00:02 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philosopher *this)
{
	struct timeval	current_time;

	sem_wait(this->forks);
	gettimeofday(&current_time, NULL);
	print_action(current_time, this, "has taken a fork");
}

void	drop_fork(t_philosopher *this)
{
	sem_post(this->forks);
}
