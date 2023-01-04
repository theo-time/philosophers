/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:42 by teliet            #+#    #+#             */
/*   Updated: 2023/01/04 18:43:18 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define NUM_PHILOSOPHERS 10

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "struct.h"
#include <sys/time.h>

void eating(t_philosopher	*this);
void sleeping(t_philosopher	*this);
void take_fork(t_philosopher *this, pthread_mutex_t *fork);
void drop_fork(pthread_mutex_t *fork);
void dies(t_philosopher *this);
void thinking(t_philosopher	*this);

#endif