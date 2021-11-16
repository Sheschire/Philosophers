/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:03:00 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/16 17:14:54 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	prompt(t_data *d, int id, char *s)
{
	int	timestamp;
	
	timestamp = get_time() - d->t_start;
	pthread_mutex_lock(&d->prompt);
	printf("%u ", timestamp);
	printf("%d ", id);
	printf("%s\n", s);
	pthread_mutex_unlock(&d->prompt);
}

int	monitor(t_data *d)
{
	int	id;
	unsigned int time;

	id = -1;
	while (++id < d->nb_philo)
	{
		time = get_time();
		if (time - d->philos[id].last_meal > d->t_die)
		{
			prompt(d, id, "died");
			exit(0);
			//end_simulation(d);
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
		philo->last_meal = get_time();
	 	usleep_opti(d->t_eat);
	 	pthread_mutex_unlock(&d->forks[philo->r_fork_id]);
	 	pthread_mutex_unlock(&d->forks[philo->l_fork_id]);
		prompt(d, philo->id, "is sleeping");
		usleep_opti(d->t_sleep);
		prompt(d, philo->id, "is thinking");
	}
	return (NULL);
}

void	start_simulation(t_data *d)
{
	int	id;

	id = -1;
	while (++id < d->nb_philo)
	{
		if (id % 2 == 1)
			usleep_opti(10);
		if (pthread_create(&d->philos[id].thread_id, NULL, &routine, (void *)&(d->philos[id])))
			_err("Failed to create a thread. (Philos)");
	}
}