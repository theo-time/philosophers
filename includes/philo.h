/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:42 by teliet            #+#    #+#             */
/*   Updated: 2023/01/06 18:55:43 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define NUM_PHILOSOPHERS 8

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "struct.h"

// Philosopher action
void			eating(t_philosopher *this);
void			sleeping(t_philosopher *this);
void			take_fork(t_philosopher *this, pthread_mutex_t *fork);
void			drop_fork(pthread_mutex_t *fork);
void			dies(t_philosopher *this);
void			thinking(t_philosopher *this);

// Parser utils
unsigned long	ft_atoi(const char *str);
void			print_timestamp(struct timeval *tv, t_params params);
long			ms_since_start(struct timeval *tv, t_params params);

// Display
void print_action(struct timeval current_time, t_philosopher *this, char *action);
void		usleep_ms(int ms);

#endif