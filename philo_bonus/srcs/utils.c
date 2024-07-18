/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:43:19 by trimize           #+#    #+#             */
/*   Updated: 2024/07/12 13:22:11 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_atoi_w(const char *nptr, int *num)
{
	int				i;
	int				sign;
	unsigned int	tp_num;

	i = 0;
	sign = 1;
	tp_num = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == ' '
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	while (48 <= nptr[i] && nptr[i] <= 57)
	{
		tp_num = tp_num * 10 + (nptr[i++] - 48);
		if (tp_num > 2147483647)
			return (0);
	}
	*num = tp_num;
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == ' '
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	while (48 <= nptr[i] && nptr[i] <= 57)
		num = num * 10 + (nptr[i++] - 48);
	return (num);
}

void	freeforks(t_threads *th, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philo)
		(sem_close(th->forks[i]), free(th->forks[i++]));
	free(th->forks);
}

void	free_philo(t_philo *philo, t_threads *th)
{
	freeforks(th, philo);
	sem_close(th->stop);
	free(th->stop);
	sem_close(th->eat);
	free(th->eat);
	sem_close(th->print);
	free(th->print);
	free(th->has_to_stop);
	free(philo);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && need_stop(philo) == 0)
		usleep(500);
	return (0);
}
