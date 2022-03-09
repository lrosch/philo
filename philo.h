/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:56:26 by lrosch            #+#    #+#             */
/*   Updated: 2022/01/26 16:44:07 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_input {
	int				nbr_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nbr_eat;
	int				waiting;
	int				death_flag;
	int				done;
	int				first;
	struct timeval	start_t;
	pthread_mutex_t	death_m;
	pthread_mutex_t	speak_m;
	pthread_mutex_t	waiting_m;
	pthread_mutex_t	done_m;

}	t_input;

typedef struct s_philo {
	struct s_input	*input;
	int				index;
	int				done_eat;
	long			alive_t;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	philo_done_m;
}	t_philo;

/* eat_sleep_repeat */
void			philo_mutex_lock(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_schleep(t_philo *philo);
int				is_dead(t_philo *philo);

/* error_checking */
int				error_checking(int argc, char **argv);
int				ft_notint(char *s);
long long int	ft_atoi(const char *str);

/* free */
void			freeall(t_philo **all, pthread_t *philo, t_input *input);
void			free_array(t_philo **all, t_input *input);

/* philo_initialize */
int				init_input_m(t_input *input);
void			init_philo(t_philo **all, int i, t_input *input);
int				init_input(int argc, char **argv, t_input *input);

/* philo_utils */
long			gettimestamp(t_philo *philo);
void			printer(t_philo *philo, char *msg, int flag);

/* philo */
void			routine(t_philo *philo);
void			start_threads(t_philo **all, t_input *input, pthread_t *philo);
void			death_check(t_philo **all, t_input *input);
void			*thread_philo(void *args);

/* edge_cases */
int				philo_one(t_philo *philo);

/* thread */
void			*thread_philo(void *args);
void			routine(t_philo *philo);

#endif
