/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:40:59 by teliet            #+#    #+#             */
/*   Updated: 2023/01/03 18:05:28 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		soup = 10;

void	*philo_loop(void *philosopher)
{
	t_philosopher	*this;

	this = (t_philosopher *)philosopher;
	while (0 < soup)
	{
		printf("Philosopher n*%d eating soup.\n", this->id);
		soup -= 1;
	}
	printf("Philosopher n*%d died.\n", this->id);
}

void	populate(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		philosophers[i].id = i;
		i++;
	}
}

int	main(void)
{
	pthread_t threads[NUM_THREADS];
	t_philosopher philosophers[NUM_THREADS];

	populate(philosophers);
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		pthread_create(&threads[i], NULL, philo_loop, &(philosophers[i]));
	}

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("soup left : %d\n", soup);
	exit(EXIT_SUCCESS);
}