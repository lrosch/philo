/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:56:17 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/18 17:54:34 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->input->waiting_m);
	philo->input->waiting++;
	pthread_mutex_unlock(&philo->input->waiting_m);
	while (philo->input->waiting != philo->input->nbr_philo + 1)
		;
	if ((philo->index % 2) == 0)
		usleep(3000);
	routine(philo);
	return (0);
}

void	routine(t_philo *philo)
{
	int	eaten;

	eaten = 0;
	if (philo_one(philo))
		return ;
	while (philo->input->death_flag == 0)
	{
		philo_eat(philo);
		eaten++;
		if (eaten == philo->input->nbr_eat && philo->input->nbr_eat != 0)
		{
			pthread_mutex_lock(&philo->input->done_m);
			philo->input->done++;
			pthread_mutex_unlock(&philo->input->done_m);
			pthread_mutex_lock(&philo->philo_done_m);
			philo->done_eat = 1;
			pthread_mutex_unlock(&philo->philo_done_m);
			return ;
		}
		if (philo->input->death_flag == 0)
			philo_schleep(philo);
	}
}
