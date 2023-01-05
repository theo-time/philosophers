/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:21:17 by teliet            #+#    #+#             */
/*   Updated: 2023/01/05 17:28:31 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_timestamp(struct timeval *tv) 
{
  long sec = tv->tv_sec;
  long ms = tv->tv_usec / 1000;
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
