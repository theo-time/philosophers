/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:14 by teliet            #+#    #+#             */
/*   Updated: 2023/02/07 12:29:52 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_model *model)
{
	sem_unlink("forks");
	sem_close(model->forks);
	sem_unlink("dead_philo");
	sem_close(model->dead_philo);
	sem_unlink("print_rights");
	sem_close(model->print_rights);
	sem_unlink("philo_fed");
	sem_close(model->philo_fed);
}
