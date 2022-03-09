/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:57:56 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/18 17:12:15 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_one(t_philo *philo)
{
	int	action_t;
	int	passed_t;

	action_t = gettimestamp(philo);
	passed_t = action_t;
	if (philo->input->nbr_philo == 1)
	{
		pthread_mutex_lock(philo->fork_l);
		printer(philo, "has taken a fork", 0);
		while (passed_t - action_t < (philo->input->tt_die / 1000))
		{
			usleep(100);
			passed_t = gettimestamp(philo);
		}
		pthread_mutex_unlock(philo->fork_r);
		return (1);
	}
	return (0);
}
