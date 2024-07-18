/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:37:02 by trimize           #+#    #+#             */
/*   Updated: 2024/07/11 14:37:09 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	eat_supp(t_philo *philo)
{
	sem_wait(philo->eat);
	sem_wait(philo->print);
	printf("%ld %d is eating\n", philo->last_ate, philo->id);
	sem_post(philo->eat);
	sem_post(philo->print);
	ft_usleep(philo->time_to_eat, philo);
	sem_wait(philo->eat);
	philo->ate++;
	sem_post(philo->eat);
}

void	eat_supp2(t_philo *philo)
{
	if (philo->num_philo == 1)
		(sem_wait(philo->print), printf("%zu %d has taken a fork\n",
				get_current_time() - philo->time, philo->id),
			sem_post(philo->print),
			ft_usleep(philo->time_to_die + 10, philo));
	if (philo->ate == philo->nb_time_eat)
		(sem_wait(philo->eat),
			sem_wait(philo->print),
			printf("%zu %d is full\n",
				get_current_time() - philo->time, philo->id),
			philo->ate_enough = 1,
			sem_post(philo->print),
			sem_post(philo->eat));
}
