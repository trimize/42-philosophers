/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:22:12 by trimize           #+#    #+#             */
/*   Updated: 2024/07/11 14:37:46 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_threads
{
	int				*has_to_stop;
	long			i;
	pthread_t		checking;
	pthread_t		*threads;
	pthread_mutex_t	*print;
	pthread_mutex_t	*eat;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*stop;
}	t_threads;

typedef struct s_philo
{
	int				right_fork;
	int				left_fork;
	int				id;
	int				is_dead;
	int				ate_enough;
	int				*has_to_stop;
	int				ate;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_eat;
	long			time;
	long			last_ate;
	pthread_mutex_t	*print;
	pthread_mutex_t	*eat;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*stop;
}	t_philo;

int			ft_usleep(size_t milliseconds, t_philo *philo);
int			need_stop(t_philo *philo);
int			ft_atoi_w(const char *nptr, int *num);
int			ft_atoi(const char *nptr);
long int	get_current_time(void);
void		check_args(char **argv, int argc);
void		init_args(char **argv, int argc, t_philo *philo, t_threads *th);
void		init_threads(t_philo *philo, t_threads *th, char **argv, int argc);
void		sleeping(t_philo *philo);
void		freeforks(t_threads *th, t_philo *philo);
void		eat(t_philo *philo);
void		died(t_philo *philo);
void		free_philo(t_philo *philo, t_threads *th);
void		*routine(void *ptr);
void		eat_supp(t_philo *philo);
void		eat_supp2(t_philo *philo);
void		check_death_supp(t_philo *philo, int i);
void		init_args_supp(t_philo *philo, t_threads *th);
void		init_th(t_threads *th, int num_philo);

#endif