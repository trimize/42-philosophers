/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:37:02 by trimize           #+#    #+#             */
/*   Updated: 2024/07/11 14:38:05 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_supp(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	pthread_mutex_lock(philo->print);
	printf("%ld %d is eating\n", philo->last_ate, philo->id);
	pthread_mutex_unlock(philo->eat);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(philo->eat);
	philo->ate++;
	pthread_mutex_unlock(philo->eat);
}

void	eat_supp2(t_philo *philo)
{
	if (philo->num_philo == 1)
		(pthread_mutex_lock(philo->print), printf("%zu %d has taken a fork\n",
				get_current_time() - philo->time, philo->id),
			pthread_mutex_unlock(philo->print),
			ft_usleep(philo->time_to_die + 10, philo));
	if (philo->ate == philo->nb_time_eat)
		(pthread_mutex_lock(philo->eat),
			pthread_mutex_lock(philo->print),
			printf("%zu %d is full\n",
				get_current_time() - philo->time, philo->id),
			philo->ate_enough = 1,
			pthread_mutex_unlock(philo->print),
			pthread_mutex_unlock(philo->eat));
}

void	init_th(t_threads *th, int num_philo)
{
	th->forks = (pthread_mutex_t **)malloc(num_philo
			* sizeof(pthread_mutex_t *));
	th->stop = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	th->eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	th->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
}
