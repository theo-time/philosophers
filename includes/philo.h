/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:42 by teliet            #+#    #+#             */
/*   Updated: 2023/01/05 17:41:49 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define NUM_PHILOSOPHERS 2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "struct.h"
#include <sys/time.h>

// Philosopher action
void eating(t_philosopher	*this);
void sleeping(t_philosopher	*this);
void take_fork(t_philosopher *this, pthread_mutex_t *fork);
void drop_fork(pthread_mutex_t *fork);
void dies(t_philosopher *this);
void thinking(t_philosopher	*this);

// Parser utils
unsigned long	ft_atoi(const char *str);
void print_timestamp(struct timeval *tv);

#endif