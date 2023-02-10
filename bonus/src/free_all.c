/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:14 by teliet            #+#    #+#             */
/*   Updated: 2023/02/10 18:15:21 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_model *model)
{
	sem_unlink("forks");
	sem_close(model->forks);
	sem_unlink("simulation_ended");
	sem_close(model->simulation_ended);
	sem_unlink("print_rights");
	sem_close(model->print_rights);
	sem_unlink("philo_fed");
	sem_close(model->philo_fed);
}
