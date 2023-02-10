/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teliet <teliet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:22:27 by teliet            #+#    #+#             */
/*   Updated: 2023/02/08 13:37:46 by teliet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_pointers(t_model *model)
{
	model->threads = NULL;
	model->forks = NULL;
	model->philosophers = NULL;
	model->print_rights = NULL;
	model->die_check_rights = NULL;
	model->sim_end_check_rights = NULL;
}
