/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:14 by teliet            #+#    #+#             */
/*   Updated: 2023/01/12 18:19:07 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_model *model)
{
	int	i;

	i = 0;
	while (i < model->params->number_of_philosophers)
	{
		pthread_mutex_destroy(model->forks + i);
		i++;
	}
	pthread_mutex_destroy(model->print_rights);
	free(model->philosophers);
	free(model->threads);
	free(model->forks);
	free(model->print_rights);
	free(model->die_check_rights);
	free(model->sim_end_check_rights);
}
