/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:06 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/18 17:56:17 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_mutex_lock(t_philo *philo)
{
	if (philo->index == philo->input->nbr_philo
		&& philo->input->nbr_philo % 2 == 1
		&& philo->input->first == 0)
	{
		pthread_mutex_lock(philo->fork_r);
		printer(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->fork_l);
		printer(philo, "has taken a fork", 0);
		philo->input->first = 1;
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		printer(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->fork_r);
		printer(philo, "has taken a fork", 0);
	}
}

void	philo_eat(t_philo *philo)
{
	int	action_t;
	int	passed_t;

	philo_mutex_lock(philo);
	action_t = gettimestamp(philo);
	passed_t = action_t;
	philo->alive_t = (gettimestamp(philo) + philo->input->tt_die / 1000);
	printer(philo, "is eating", 0);
	while (passed_t - action_t < (philo->input->tt_eat / 1000))
	{
		if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->fork_r);
			pthread_mutex_unlock(philo->fork_l);
			return ;
		}
		usleep(100);
		passed_t = gettimestamp(philo);
	}
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	philo_schleep(t_philo *philo)
{
	int	action_t;
	int	passed_t;

	action_t = gettimestamp(philo);
	passed_t = action_t;
	printer(philo, "is sleeping", 0);
	while (passed_t - action_t < (philo->input->tt_sleep / 1000))
	{
		if (is_dead(philo) == 1)
			return ;
		usleep(100);
		passed_t = gettimestamp(philo);
	}
	printer(philo, "is thinking", 0);
}

int	is_dead(t_philo *philo)
{
	long	eat_time;

	eat_time = gettimestamp(philo);
	pthread_mutex_lock(&philo->input->death_m);
	if (philo->input->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->input->death_m);
		return (1);
	}
	if (philo->alive_t <= eat_time)
	{	
		if (philo->input->death_flag != 1)
		{
			pthread_mutex_unlock(&philo->input->death_m);
			printer(philo, "has died", 1);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->input->death_m);
	return (0);
}
