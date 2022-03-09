/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:56:24 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/27 14:19:38 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_check(t_philo **all, t_input *input)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < input->nbr_philo)
		{
			pthread_mutex_lock(&input->done_m);
			if (input->done == input->nbr_philo)
			{
				pthread_mutex_unlock(&input->done_m);
				input->death_flag = 1;
				return ;
			}
			pthread_mutex_unlock(&input->done_m);
			pthread_mutex_lock(&all[i]->philo_done_m);
			if (!all[i]->done_eat)
			{
				if (is_dead(all[i]))
					return ;
			}
			pthread_mutex_unlock(&all[i]->philo_done_m);
		}
		i = 0;
	}
}

void	start_threads(t_philo **all, t_input *input, pthread_t *philo)
{
	int	i;

	i = 0;
	while ((*all)->input->waiting != (*all)->input->nbr_philo)
		;
	pthread_mutex_lock(&(*all)->input->waiting_m);
	gettimeofday(&input->start_t, NULL);
	(*all)->input->waiting++;
	pthread_mutex_unlock(&(*all)->input->waiting_m);
	i = 0;
	death_check(all, input);
	while (i < input->nbr_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	freeall(all, philo, input);
}

void	create_threads(t_philo **all, t_input *input, pthread_t *philo)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		init_philo(all, i, input);
		i++;
	}
	all[0]->fork_r = all[input->nbr_philo - 1]->fork_l;
	i = 0;
	while (i < input->nbr_philo)
	{
		pthread_create(&philo[i], NULL, thread_philo, all[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_input		input;
	t_philo		**all;
	pthread_t	*philo;

	if (!init_input(argc, argv, &input))
		return (0);
	all = malloc(sizeof(t_philo *) * input.nbr_philo);
	if (!all)
	{
		freeall(NULL, NULL, &input);
		return (1);
	}
	philo = malloc(sizeof(pthread_t) * input.nbr_philo);
	if (!philo)
	{
		freeall(all, NULL, &input);
		return (1);
	}
	create_threads(all, &input, philo);
	start_threads(all, &input, philo);
	return (0);
}
