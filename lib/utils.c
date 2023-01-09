/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:21:17 by teliet            #+#    #+#             */
/*   Updated: 2023/01/09 18:55:47 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long now(t_philosopher *this) 
{
  	struct timeval tv;
 	gettimeofday(&tv, NULL);
  	return (time_elapsed(this->params->simulation_start, tv));
}


void    ft_usleep(t_philosopher *this, time_t time)
{
    time_t    goal;

    goal = 0;
    goal = now(this) + time;
    while (now(this) < goal)
    {
        pthread_mutex_lock(this->die_check_rights);
        if (this->params->dead_philo)
        {
            pthread_mutex_unlock(this->die_check_rights);
            break ;
        }
        pthread_mutex_unlock(this->die_check_rights);
        usleep(50);
    }
}


long ms_since_start(struct timeval *tv, t_params params) 
{

//   printf("time since : %ld", elapsed_time);
  return ((tv->tv_sec - params.simulation_start.tv_sec) * 1000 + (tv->tv_usec - params.simulation_start.tv_usec) / 1000);
}

void print_timestamp(struct timeval *tv, t_params params) 
{
  long sec = tv->tv_sec - params.simulation_start.tv_sec;
  long ms = (tv->tv_usec - params.simulation_start.tv_usec) / 1000;
  long elapsed_time = sec * 1000 + ms;
  printf("%ld", elapsed_time);
}

size_t	ft_strlen(const char *str)
{
	unsigned long int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned long	ft_atoi(const char *str)
{
	unsigned long	sign;
	unsigned long	result;

	result = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (sign * result);
}

int	is_integer(char *str)
{
	if (ft_strlen(str) > 11 || *str == 0)
		return (0);
	if (*str == '-' && str[1])
		str++;
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}
