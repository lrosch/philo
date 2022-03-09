/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:00:12 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/18 17:08:27 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettimestamp(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec - philo->input->start_t.tv_sec) * 1000)
		+ ((time.tv_usec - philo->input->start_t.tv_usec) / 1000));
}

void	printer(t_philo *philo, char *msg, int flag)
{
	pthread_mutex_lock(&philo->input->speak_m);
	pthread_mutex_lock(&philo->input->death_m);
	if (philo->input->death_flag != 1)
	{
		printf("%li %i %s\n", gettimestamp(philo), philo->index, msg);
	}
	if (flag == 1)
		philo->input->death_flag = 1;
	pthread_mutex_unlock(&philo->input->death_m);
	pthread_mutex_unlock(&philo->input->speak_m);
}
