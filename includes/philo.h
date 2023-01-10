/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:42 by teliet            #+#    #+#             */
/*   Updated: 2023/01/10 16:57:28 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "structs.h"

// Philosopher action
void			eating(t_philosopher *this);
void			sleeping(t_philosopher *this);
void			take_fork(t_philosopher *this, pthread_mutex_t *fork);
void			drop_fork(pthread_mutex_t *fork);
void			dies(t_philosopher *this);
void			thinking(t_philosopher *this);

// Parser utils
unsigned long	ft_atoi(const char *str);

// Display
void			print_action(struct timeval t, t_philosopher *this, char *act);

// Time
int				time_elapsed(struct timeval start_time, struct timeval time);
void			ft_usleep(t_philosopher *this, time_t time);
int				is_dead(t_philosopher *this, struct timeval time);
int				finished_eating(t_philosopher *this, struct timeval time);
int				finished_sleeping(t_philosopher *this, struct timeval time);
int				finished_thinking(t_philosopher *this, struct timeval time);
void			print_timestamp(struct timeval *tv, t_params params);

// Misc
void			free_all(t_model *model);
// void populate(t_model *model, t_params *params, pthread_mutex_t *die_check_rights, pthread_mutex_t *print_rights);

#endif