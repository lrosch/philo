/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:56:29 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/18 17:55:40 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_input(int argc, char **argv, t_input *input)
{
	if (!error_checking(argc, argv))
		return (0);
	input->nbr_philo = ft_atoi(argv[1]);
	input->tt_die = (ft_atoi(argv[2]) * 1000);
	input->tt_eat = (ft_atoi(argv[3]) * 1000);
	input->tt_sleep = (ft_atoi(argv[4]) * 1000);
	input->waiting = 0;
	input->death_flag = 0;
	input->done = 0;
	input->first = 0;
	if (argc == 6)
		input->nbr_eat = ft_atoi(argv[5]);
	else
		input->nbr_eat = 0;
	if (init_input_m(input))
		return (0);
	else
		return (1);
}

int	init_input_m(t_input *input)
{
	pthread_mutex_init(&input->death_m, NULL);
	pthread_mutex_init(&input->speak_m, NULL);
	pthread_mutex_init(&input->waiting_m, NULL);
	pthread_mutex_init(&input->done_m, NULL);
	return (0);
}

void	init_philo(t_philo **all, int i, t_input *input)
{
	all[i] = malloc(sizeof(t_philo));
	all[i]->input = input;
	all[i]->fork_l = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(all[i]->fork_l, NULL);
	pthread_mutex_init(&all[i]->philo_done_m, NULL);
	all[i]->done_eat = 0;
	all[i]->alive_t = input->tt_die / 1000;
	if (i != 0)
		all[i]->fork_r = all[i - 1]->fork_l;
	all[i]->index = i + 1;
}
