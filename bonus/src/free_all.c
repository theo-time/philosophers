/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:14 by teliet            #+#    #+#             */
/*   Updated: 2023/01/11 16:26:31 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_model *model)
{
	sem_close(model->forks);
	sem_unlink("forks");
	sem_close(model->die_check_rights);
	sem_unlink("die_check_rights");
	sem_close(model->print_rights);
	sem_unlink("print_rights");
	free(model->philosophers);
}
