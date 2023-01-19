/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:14 by teliet            #+#    #+#             */
/*   Updated: 2023/01/19 12:09:37 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_model *model)
{
	free(model->philosophers);
	free(model->pid_list);
	sem_close(model->forks);
	sem_unlink("forks");
	sem_close(model->dead_philo);
	sem_unlink("dead_philo");
	sem_close(model->print_rights);
	sem_unlink("print_rights");
	sem_close(model->philo_fed);
	sem_unlink("philo_fed");
}
