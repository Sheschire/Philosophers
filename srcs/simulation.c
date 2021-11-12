/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:03:00 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/12 23:41:17 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prompt(t_data *d, int id, char *s)
{
	pthread_mutex_lock(&d->prompt);
	printf("timestamp ");
	printf("%d ", id);
	printf("%s\n", s);
	pthread_mutex_unlock(&d->prompt);
}

int	monitor(t_data *d)
{
	int	id;
	
	id = -1;
	while (++id < d->nb_philo)
	{
		if (d->philos[id].alive == 0)
		{
			pthread_mutex_lock(&d->prompt);
			prompt(d, id, "has died");
			pthread_mutex_unlock(&d->prompt);
			end_simulation(d);
		}
	}
	return (1);
}

void	*routine(void *thread_philo)
{
	t_philo	*philo;
	t_data *d;
	
	philo = (t_philo *)thread_philo;
	d = philo->d;
	while (monitor(d))
	{
		pthread_mutex_lock(&d->forks[philo->r_fork_id]);
		prompt(d, philo->id, "has taken a fork");
	 	pthread_mutex_lock(&d->forks[philo->l_fork_id]);
		prompt(d, philo->id, "has taken a fork");
		prompt(d, philo->id, "is eating");
		philo->ate = 1;
		philo->last_meal = time_since_beginning(philo);
	 	usleep(d->t_eat);
	 	pthread_mutex_unlock(&d->forks[philo->r_fork_id]);
	 	pthread_mutex_unlock(&d->forks[philo->l_fork_id]);
		prompt(d, philo->id, "is sleeping");
		usleep(d->t_sleep);
		prompt(d, philo->id, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_data *d)
{
	int	id;

	id = -1;
	while (++id < d->nb_philo)
		if (id % 2 == 0)
			if (pthread_create(&d->philos[id].thread_id, NULL, &routine, (void *)&(d->philos[id])))
				_err("Failed to create a thread. (Philos)");
	id = -1;
	usleep(1500);
	while (++id < d->nb_philo)
		if (id % 2 == 1)
			if (pthread_create(&d->philos[id].thread_id, NULL, &routine, (void *)&(d->philos[id])))
				_err("Failed to create a thread. (Philos)");
}