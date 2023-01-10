/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:36:43 by teliet            #+#    #+#             */
/*   Updated: 2023/01/10 17:05:16 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_params
{
	struct timeval	simulation_start;
	int				dead_philo;
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				eat_before_end;
}					t_params;

typedef struct s_model
{
	pthread_t		*threads;
	pthread_mutex_t	*print_rights;
	pthread_mutex_t	*die_check_rights;
	pthread_mutex_t	*forks;
	void			*philosophers;
	t_params		*params;
}					t_model;

// State 0 : thinking, state 1 : eating, state 2 : sleeping
typedef struct s_philosopher
{
	int				id;
	int				alive;
	int				state;
	int				eat_before_end;
	int				nb_meals;
	struct timeval	last_meal_time;
	struct timeval	last_sleep_time;
	struct timeval	start_think_time;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_rights;
	pthread_mutex_t	*die_check_rights;
	t_params		*params;
	t_model			*model;
}					t_philosopher;

#endif