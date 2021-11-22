/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:12:20 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/16 15:56:40 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	usleep_opti(unsigned int ms_time)
{
	unsigned int start;

    start = 0;
    start = get_time();
    while ((get_time() - start) < ms_time)
        usleep(ms_time / 10);
}

void	_err(char *s)
{
	printf("Error\n%s\n", s);
	exit(0);
}

void	end_simulation(t_data *d)
{
	int	id;

	id = -1;
	while (++id < d->nb_philo)
	{
		pthread_mutex_destroy(&d->forks[id]);
		pthread_mutex_destroy(&d->philos[id].lock_meal);
	}
	pthread_mutex_destroy(&d->prompt);
	pthread_mutex_destroy(&d->update_nb_meal);
	pthread_mutex_destroy(&d->check_end);
	free(d->philos);
	free(d->forks);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
