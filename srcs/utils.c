/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:12:20 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/12 23:02:44 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_debug(t_data *d)
{
	int	id;

	printf("--------------------\n");
	printf("|       DATA       |\n");
	printf("--------------------\n");
	printf("nb_philo = %d\n", d->nb_philo);
	printf("t_die = %d\n", d->t_die);
	printf("t_eat = %d\n", d->t_eat);
	printf("t_sleep = %d\n", d->t_sleep);
	printf("nb_to_eat = %d\n", d->nb_to_eat);
	printf("everyon_alive = %d\n\n", d->everyone_alive);
	printf("--------------------\n");
	printf("|       PHILO      |\n");
	printf("--------------------\n");

	id = -1;
	while (++id < d->nb_philo)
	{
		printf("--------------------\n");
		printf("      Philo n.%d     \n", id);
		printf("--------------------\n");
		printf("d->philos[%d].id = %d\n", id, d->philos[id].id);
		printf("d->philos[%d].ate = %d\n", id, d->philos[id].ate);
		printf("d->philos[%d].alive = %d\n", id, d->philos[id].alive);
		printf("d->philos[%d].nb_meal = %d\n", id, d->philos[id].nb_meal);
		printf("d->philos[%d].l_fork_id = %d\n", id, d->philos[id].l_fork_id);
		printf("d->philos[%d].r_fork_id = %d\n", id, d->philos[id].r_fork_id);
		printf("d->philos[%d].start_time = %d\n", id, d->philos[id].start_time);
		printf("d->philos[%d].last_meal = %d\n", id, d->philos[id].last_meal);
	}
}

unsigned int	get_time(void)
{
	struct timeval	s_time;
	unsigned int	time;
	
	time = (unsigned int)gettimeofday(&s_time, NULL);
	time = (unsigned int)s_time.tv_sec * 1000 + (unsigned int)s_time.tv_usec / 1000;
	return (time);
}

unsigned int	time_since_beginning(t_philo *philo)
{
	return (get_time() - philo->start_time);
}

void	_err(char *s)
{
	printf("Error\n%s\n", s);
	exit(0);
}

void	end_simulation(t_data *d)
{
	int	id;

	id = 0;
	pthread_mutex_destroy(&d->prompt);
	while (++id < d->nb_philo)
	{
		pthread_mutex_destroy(&d->forks[id]);
	}
	exit(0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	minus;

	nb = 0;
	minus = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb * minus);
}

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;
	
	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (0);
	}
	return (1);
}
