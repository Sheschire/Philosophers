/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:16:02 by tlemesle          #+#    #+#             */
/*   Updated: 2021/10/27 16:00:08 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	int	id;

	id = -1;
	t_data	d;
	if (!check_arg(ac, av))
		_err("Arguments are not valids.");
	init_data(&d, av);
	init_philos(&d);
	unsigned int time;
	
	time = get_time();
	printf("%u\n", time);
//	start_simulation(&d);
	// while (++id < d.nb_philo)
	// 	if (pthread_join(d.philos[id].thread_id, NULL))
	// 		_err("Failed in joining thread.");
	return (0);
}
