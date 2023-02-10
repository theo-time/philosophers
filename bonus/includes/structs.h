/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:36:43 by teliet            #+#    #+#             */
/*   Updated: 2023/01/26 13:30:03 by teliet           ###   ########.fr       */
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
	int				fed_end_mode;
}					t_params;

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
	sem_t			*forks;
	sem_t			*print_rights;
	sem_t			*dead_philo;
	sem_t			*philo_fed;
	pthread_t		wait_thread;
	t_params		*params;
}					t_philosopher;

typedef struct s_model
{
	sem_t			*print_rights;
	sem_t			*dead_philo;
	sem_t			*philo_fed;
	sem_t			*forks;
	pid_t			pid_list[200];
	t_philosopher	philosophers[200];
	t_params		*params;
}					t_model;

#endif