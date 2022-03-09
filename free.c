/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:57:07 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/18 17:47:53 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeall(t_philo **all, pthread_t *philo, t_input *input)
{
	pthread_mutex_destroy(&input->death_m);
	pthread_mutex_destroy(&input->waiting_m);
	pthread_mutex_destroy(&input->speak_m);
	pthread_mutex_destroy(&input->done_m);
	free_array(all, input);
	if (all != NULL)
		free(all);
	if (philo != NULL)
		free(philo);
}

void	free_array(t_philo **all, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		if (all[i]->fork_l)
		{
			pthread_mutex_destroy(all[i]->fork_l);
			free(all[i]->fork_l);
		}
		pthread_mutex_destroy(&all[i]->philo_done_m);
		if (all[i])
			free(all[i]);
		i++;
	}
}
