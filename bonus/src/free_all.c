/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:14 by teliet            #+#    #+#             */
/*   Updated: 2023/01/18 13:45:28 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_this(t_model *model)
{
	free(model->philosophers);
	free(model->pid_list);
}

void	free_sems(t_model *model)
{
	sem_close(model->forks);
	sem_unlink("forks");
	sem_close(model->dead_philo);
	sem_unlink("dead_philo");
	sem_close(model->print_rights);
	sem_unlink("print_rights");
	sem_close(model->simulation_play);
	sem_unlink("simulation_play");
}
