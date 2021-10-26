/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:03:00 by tlemesle          #+#    #+#             */
/*   Updated: 2021/10/26 16:45:09 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prompt(t_data *d, int id, char *s)
{
	pthread_mutex_lock(&d->prompt);
	printf("timestamp ");
	printf("%d ", id);
	printf("%s", s);
	pthread_mutex_unlock(&d->prompt);
}

int	monitor(t_data *d)
{
	int	id;
	
	id = 0;
	while (++id <= d->nb_philo)
	{
		if (d->philos[id].alive == 0)
		{
			pthread_mutex_lock(&d->prompt);
			printf("timestamp_in_ms %d died", id);
			pthread_mutex_unlock(&d->prompt);
			end_simulation(d);
		}
	}
	return (1);
}

void	*routine(t_data *d)
{
	// while (d->philos[id].alive && d->everyone_alive)
	// {
		pthread_mutex_lock(&d->forks[id]);
		prompt(d, id, "has taken a fork\n");
	 	pthread_mutex_lock(&d->forks[id + 1]);
		prompt(d, id, "has taken a fork\n");
		prompt(d, id, "is eating\n");
	 	usleep(d->t_eat);
	 	pthread_mutex_unlock(&d->forks[id]);
	 	pthread_mutex_unlock(&d->forks[id + 1]);
		prompt(d, id, "is sleeping\n");
		usleep(d->t_sleep);
		prompt(d, id, "is thinking\n");
	// }
	return (NULL);
}

void	start_simulation(t_data *d)
{
	int	id;

	id = -1;
	while (++id <= d->nb_philo)
		if (id % 2 == 0)
			if (pthread_create(&d->philos[id].thread_id, NULL, routine(d), d))
				_err("Failed to create a thread. (Philos)");
	id = -1;
	usleep(20);
	while (++id <= d->nb_philo)
		if (id % 2 == 1)
			if (pthread_create(&d->philos[id].thread_id, NULL, routine(d), d))
				_err("Failed to create a thread. (Philos)");
}