/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:23:07 by tlemesle          #+#    #+#             */
/*   Updated: 2021/10/14 16:38:45 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *d, char **av)
{
	d->nb_philo = ft_atoi(av[1]);
	if (d->nb_philo > 250)
		_err("Too many Philosophers for the simulation.");
	if (d->nb_philo < 2)
		_err("Not enough Philosophers for the simulation.");
	d->t_die = ft_atoi(av[2]);
	d->t_eat = ft_atoi(av[3]);
	d->t_sleep = ft_atoi(av[4]);
	d->nb_to_eat = -1;
	if (av[5])
		d->nb_to_eat = ft_atoi(av[5]);
	d->everyone_alive = 1;
}

void	init_philos(t_data *d)
{
	int	id;

	id = 0;
	while (++id <= d->nb_philo)
	{
		d->philos[id].id = id;
		d->philos[id].ate = 0;
		d->philos[id].alive = 1;
		d->philos[id].nb_meal = 0;
		d->philos[id].l_fork_id = id + 1;
		d->philos[id].r_fork_id = id;
		if (pthread_mutex_init(&d->forks[id], NULL))
			_err("Mutex init failed. (forks)");
	}
	if (pthread_mutex_init(&d->prompt, NULL))
		_err("Mutex init failed. (prompt)");
}