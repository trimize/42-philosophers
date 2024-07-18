/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:46:38 by trimize           #+#    #+#             */
/*   Updated: 2024/07/12 13:22:38 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_current_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	need_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	pthread_mutex_lock(philo->stop);
	if (philo->has_to_stop[0] == 1 || philo->is_dead == 1
		|| philo->ate_enough == 1)
		return (pthread_mutex_unlock(philo->eat),
			pthread_mutex_unlock(philo->stop), 1);
	return (pthread_mutex_unlock(philo->eat),
		pthread_mutex_unlock(philo->stop), 0);
}

void	died(t_philo *philo)
{
	pthread_mutex_lock(philo->stop);
	philo->is_dead = 1;
	philo->has_to_stop[0] = 1;
	pthread_mutex_unlock(philo->stop);
}

void	eat(t_philo *philo)
{
	if (need_stop(philo) == 0 && philo->num_philo > 1)
	{
		pthread_mutex_lock(philo->forks[philo->left_fork]);
		if (need_stop(philo) == 0)
			(pthread_mutex_lock(philo->print),
				printf("%zu %d has taken a fork\n",
					get_current_time() - philo->time, philo->id),
				pthread_mutex_unlock(philo->print));
		pthread_mutex_lock(philo->forks[philo->right_fork]);
		if (need_stop(philo) == 0)
			(pthread_mutex_lock(philo->print),
				printf("%zu %d has taken a fork\n",
					get_current_time() - philo->time, philo->id),
				pthread_mutex_unlock(philo->print));
		pthread_mutex_lock(philo->eat);
		philo->last_ate = get_current_time() - philo->time;
		pthread_mutex_unlock(philo->eat);
		if (need_stop(philo) == 0)
			eat_supp(philo);
		pthread_mutex_unlock(philo->forks[philo->right_fork]);
		pthread_mutex_unlock(philo->forks[philo->left_fork]);
	}
	eat_supp2(philo);
}

int	main(int argc, char **argv)
{
	int			i;
	int			num_philo;
	t_philo		*philo;
	t_threads	th;

	i = 0;
	(check_args(argv, argc), num_philo = 0);
	if (!ft_atoi_w(argv[1], &num_philo) || num_philo == 0)
		return (printf("Overflow or 0 philosophers."), 1);
	philo = (t_philo *)malloc(num_philo * sizeof(t_philo));
	init_th(&th, num_philo);
	(pthread_mutex_init(th.eat, NULL), pthread_mutex_init(th.stop, NULL));
	pthread_mutex_init(th.print, NULL);
	th.has_to_stop = (int *)malloc(sizeof(int));
	th.has_to_stop[0] = 0;
	while (i < num_philo)
	{
		th.forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(th.forks[i++], NULL);
	}
	init_threads(philo, &th, argv, argc);
	(free_philo(philo, &th), free(th.threads));
}
