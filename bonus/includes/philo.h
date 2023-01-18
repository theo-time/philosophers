/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:42 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 13:49:32 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "structs.h"

// Philosopher action
void			eating(t_philosopher *this);
void			sleeping(t_philosopher *this);
void			take_fork(t_philosopher *this);
void			drop_fork(t_philosopher *this);
void			dies(t_philosopher *this);
void			thinking(t_philosopher *this);

// Parser utils
unsigned long	ft_atoi(const char *str);
int				is_integer(char *str);

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

// Init
void			populate(t_model *model);
int				get_params(t_params *params, int argc, char **argv);
int				get_model(t_model *model, t_params *params);
int				init_forks(t_model *model);

// close program
void			free_all(t_model *model);
void			end_of_simulation(t_philosopher *this);
int	            simulation_ended(t_philosopher *this);
void	        free_this(t_model *model);
void	        free_sems(t_model *model);
int             check_play(t_philosopher *this);

// Errors
void			fork_error(void);

#endif