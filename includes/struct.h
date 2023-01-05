/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:36:43 by teliet            #+#    #+#             */
/*   Updated: 2023/01/05 17:29:25 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

// State 0 : thinking, state 1 : eating, state 2 : sleeping
typedef struct s_philosopher
{
	int				id;
	int				alive;
	int				state;
	struct timeval	last_meal_time;
	struct timeval	last_sleep_time;
	struct timeval	start_think_time;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_rights;
}					t_philosopher;

typedef struct s_params
{
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
}					t_params;


#endif