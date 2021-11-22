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

void	update_nb_meal(t_data *d, t_philo *philo)
{
	pthread_mutex_lock(&d->update_nb_meal);
	philo->nb_meal++;
	if (philo->nb_meal == d->nb_to_eat)
		d->g_nb_meal++;
	pthread_mutex_unlock(&d->update_nb_meal);
}

int	check_end_philo(t_data *d)
{
	pthread_mutex_lock(&d->check_end);
	pthread_mutex_lock(&d->update_nb_meal);
	if (!d->everyone_alive || \
	(d->g_nb_meal == d->nb_philo && d->nb_to_eat != -1))
	{
		pthread_mutex_unlock(&d->update_nb_meal);
		pthread_mutex_unlock(&d->check_end);
		return (0);
	}
	pthread_mutex_unlock(&d->update_nb_meal);
	pthread_mutex_unlock(&d->check_end);
	return (1);
}

int	check_end_monitor(t_data *d, t_philo *philo)
{
	unsigned int	last_meal;

	pthread_mutex_lock(&philo->lock_meal);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->lock_meal);
	if (get_time() - last_meal > d->t_die)
	{
		prompt(d, philo->id, "died");
		pthread_mutex_lock(&d->check_end);
		d->everyone_alive = 0;
		pthread_mutex_unlock(&d->check_end);
		return (0);
	}
	pthread_mutex_lock(&d->update_nb_meal);
	if (d->g_nb_meal == d->nb_philo)
	{
		pthread_mutex_unlock(&d->update_nb_meal);
		return (0);
	}
	pthread_mutex_unlock(&d->update_nb_meal);
	usleep_opti(5);
	return (1);
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
