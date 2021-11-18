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

	pthread_mutex_lock(&d->prompt);
	timestamp = get_time() - d->t_start;
	printf("%u %d %s\n", timestamp, id + 1, s);
	if (ft_strcmp(s, "died"))
		pthread_mutex_unlock(&d->prompt);
}

void	*monitor(void *thread_philo)
{
	t_philo *philo;
	t_data *d;
	unsigned int time;

	philo = (t_philo *)thread_philo;
	d = philo->d;
	time = 0;
	while (philo->alive)
	{
		pthread_mutex_lock(&d->die_prompt);
		time = get_time();
		if (time - philo->last_meal > d->t_die)
		{
			prompt(d, philo->id, "died");
			end_simulation(d);
		}
		pthread_mutex_unlock(&d->die_prompt);
		if (d->g_nb_meal == d->nb_philo)
			end_simulation(d);
		usleep_opti(5);
	}
	return (NULL);
}


void	update_nb_meal(t_data *d, t_philo *philo)
{
	philo->nb_meal++;
	if (philo->nb_meal == d->nb_to_eat)
	{
		pthread_mutex_lock(&d->update_nb_meal);
		d->g_nb_meal++;
		pthread_mutex_unlock(&d->update_nb_meal);
	}
}

void	*routine(void *thread_philo)
{
	t_philo	*philo;
	t_data *d;
	
	philo = (t_philo *)thread_philo;
	d = philo->d;
	if (pthread_create(&d->monitor, NULL, &monitor, philo))
			_err("Failed to create a thread. (Monitor)");
	while (philo->alive)
	{
		pthread_mutex_lock(&d->forks[philo->r_fork_id]);
		prompt(d, philo->id, "has taken a fork");
	 	pthread_mutex_lock(&d->forks[philo->l_fork_id]);
		prompt(d, philo->id, "has taken a fork");
		prompt(d, philo->id, "is eating");
		philo->last_meal = get_time();
	 	usleep_opti(d->t_eat);
	 	pthread_mutex_unlock(&d->forks[philo->r_fork_id]);
	 	pthread_mutex_unlock(&d->forks[philo->l_fork_id]);
		update_nb_meal(d, philo);
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
			usleep_opti(5);
		if (pthread_create(&d->philos[id].thread_id, NULL, &routine, (void *)&(d->philos[id])))
			_err("Failed to create a thread. (Philos)");
	}
}