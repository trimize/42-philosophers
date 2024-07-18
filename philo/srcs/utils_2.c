/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:18:26 by trimize           #+#    #+#             */
/*   Updated: 2024/03/29 19:41:22 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu %d is sleeping\n",
		get_current_time() - philo->time, philo->id);
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->time_to_sleep, philo);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 10, philo);
	while (1)
	{
		if (need_stop(philo) == 0)
			eat(philo);
		if ((need_stop(philo) == 1))
			break ;
		if (need_stop(philo) == 0 && philo->num_philo > 1)
			sleeping(philo);
		if ((need_stop(philo) == 1))
			break ;
		if (need_stop(philo) == 0 && philo->num_philo > 1)
			(pthread_mutex_lock(philo->print), printf("%zu %d is thinking\n",
					get_current_time() - philo->time, philo->id),
				pthread_mutex_unlock(philo->print));
	}
	return (NULL);
}

void	check_death_supp(t_philo *philo, int i)
{
	pthread_mutex_lock(philo[0].print);
	(printf("%zu %d died\n",
			get_current_time() - philo[i].time, philo[i].id),
		died(&philo[i]));
	pthread_mutex_unlock(philo[0].eat);
	pthread_mutex_unlock(philo[0].print);
}

void	*check_death(void *ptr)
{
	int		i;
	int		ate;
	t_philo	*philo;

	i = 0;
	ate = 0;
	philo = ptr;
	while (1)
	{
		pthread_mutex_lock(philo[0].eat);
		if ((get_current_time() - philo[i].time) - philo[i].last_ate
			> philo[i].time_to_die && philo[i].ate_enough == 0)
		{
			check_death_supp(philo, i);
			break ;
		}
		if (philo[i].ate_enough == 1)
			ate++;
		(pthread_mutex_unlock(philo->eat), i++);
		if (i == philo[0].num_philo)
			i = 0;
		if (ate == philo[0].num_philo)
			break ;
	}
	return (NULL);
}

void	init_threads(t_philo *philo, t_threads *th, char **argv, int argc)
{
	th->i = 0;
	th->threads = (pthread_t *)malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
	while (th->i < ft_atoi(argv[1]))
	{
		init_args(argv, argc, &philo[th->i], th);
		pthread_create(&th->threads[th->i],
			NULL, &routine, &philo[th->i]);
		th->i++;
	}
	pthread_create(&th->checking, NULL, &check_death, philo);
	th->i = 0;
	pthread_join(th->checking, NULL);
	while (th->i < ft_atoi(argv[1]))
		pthread_join(th->threads[th->i++], NULL);
}
