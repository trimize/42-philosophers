/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:21:55 by trimize           #+#    #+#             */
/*   Updated: 2024/07/12 13:21:05 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_args(char **argv, int argc)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	if (argc < 5 || argc > 6)
		(printf("Wrong number of arguments\n"), exit(EXIT_FAILURE));
	else if (argc <= 6)
	{
		while (i < argc)
		{
			while (argv[i][y])
			{
				if (argv[i][y] < 48 || argv[i][y] > 57)
					(printf("Argument is not a number\n"), exit(EXIT_FAILURE));
				y++;
			}
			y = 0;
			i++;
		}
	}
}

void	init_args_supp_2(char **argv, t_philo *philo, t_threads *th, int argc)
{
	philo->num_philo = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->nb_time_eat = 0;
	if (argc >= 5)
	{
		if (!ft_atoi_w(argv[1], &philo->num_philo)
			|| !ft_atoi_w(argv[2], &philo->time_to_die)
			|| !ft_atoi_w(argv[3], &philo->time_to_eat)
			|| !ft_atoi_w(argv[4], &philo->time_to_sleep))
		{
			printf("Overflow\n");
			(free_philo(philo, th), free(th->threads), exit(EXIT_FAILURE));
		}
	}
}

void	init_args_supp(t_philo *philo, t_threads *th)
{
	philo->last_ate = 0;
	philo->ate = 0;
	philo->ate_enough = 0;
	philo->eat = th->eat;
	philo->print = th->print;
}

void	init_args(char **argv, int argc, t_philo *philo, t_threads *th)
{
	init_args_supp_2(argv, philo, th, argc);
	if (argc == 6)
	{
		if (!ft_atoi_w(argv[5], &philo->nb_time_eat))
		{
			printf("Overflow\n");
			(free_philo(philo, th), free(th->threads), exit(EXIT_FAILURE));
		}
	}
	else
		philo->nb_time_eat = -1;
	philo->right_fork = th->i;
	philo->left_fork = th->i - 1;
	if (th->i == 0)
		philo->left_fork = ft_atoi(argv[1]) - 1;
	philo->forks = th->forks;
	philo->stop = th->stop;
	philo->has_to_stop = th->has_to_stop;
	philo->id = th->i + 1;
	philo->time = get_current_time();
	philo->is_dead = 0;
	init_args_supp(philo, th);
}
