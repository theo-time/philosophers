/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:42 by teliet            #+#    #+#             */
/*   Updated: 2023/01/09 18:27:36 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

void free_all(pthread_t *threads,pthread_mutex_t *print_rights, pthread_mutex_t *forks, t_philosopher *philosophers, int nb_philosophers);


// Time 
int     time_elapsed(struct timeval start_time, struct timeval current_time);
void    ft_usleep(t_philosopher *this, time_t time);

#endif