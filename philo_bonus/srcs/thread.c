/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:46:38 by trimize           #+#    #+#             */
/*   Updated: 2024/07/12 13:22:21 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
	sem_wait(philo->eat);
	sem_wait(philo->stop);
	if (philo->has_to_stop[0] == 1 || philo->is_dead == 1
		|| philo->ate_enough == 1)
		return (sem_post(philo->eat),
			sem_post(philo->stop), 1);
	return (sem_post(philo->eat),
		sem_post(philo->stop), 0);
}

void	died(t_philo *philo)
{
	sem_wait(philo->stop);
	philo->is_dead = 1;
	philo->has_to_stop[0] = 1;
	sem_post(philo->stop);
}

void	eat(t_philo *philo)
{
	if (need_stop(philo) == 0 && philo->num_philo > 1)
	{
		sem_wait(philo->forks[philo->left_fork]);
		if (need_stop(philo) == 0)
			(sem_wait(philo->print),
				printf("%zu %d has taken a fork\n",
					get_current_time() - philo->time, philo->id),
				sem_post(philo->print));
		sem_wait(philo->forks[philo->right_fork]);
		if (need_stop(philo) == 0)
			(sem_wait(philo->print),
				printf("%zu %d has taken a fork\n",
					get_current_time() - philo->time, philo->id),
				sem_post(philo->print));
		sem_wait(philo->eat);
		philo->last_ate = get_current_time() - philo->time;
		sem_post(philo->eat);
		if (need_stop(philo) == 0)
			eat_supp(philo);
		sem_post(philo->forks[philo->right_fork]);
		sem_post(philo->forks[philo->left_fork]);
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
	num_philo = 0;
	check_args(argv, argc);
	if (!ft_atoi_w(argv[1], &num_philo) || num_philo == 0)
		return (printf("Overflow or 0 philosophers."), 1);
	philo = (t_philo *)malloc(num_philo * sizeof(t_philo));
	th.forks = (sem_t **)malloc(num_philo * sizeof(sem_t *));
	th.stop = (sem_t *)malloc(sizeof(sem_t));
	th.eat = (sem_t *)malloc(sizeof(sem_t));
	th.print = (sem_t *)malloc(sizeof(sem_t));
	(sem_init(th.eat, 0, 1), sem_init(th.stop, 0, 1));
	(sem_init(th.print, 0, 1), th.has_to_stop = (int *)malloc(sizeof(int)));
	th.has_to_stop[0] = 0;
	while (i < ft_atoi(argv[1]))
	{
		th.forks[i] = (sem_t *)malloc(sizeof(sem_t));
		sem_init(th.forks[i++], 0, 1);
	}
	init_threads(philo, &th, argv, argc);
	(free_philo(philo, &th), free(th.threads));
}
