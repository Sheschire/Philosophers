/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:16:02 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/12 23:40:27 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data	d;
	
	if (!check_arg(ac, av))
		_err("Arguments are not valids.");
	init_data(&d, av);
	init_philos(&d);
//	print_debug(&d);
	start_simulation(&d);
	// while (++id < d.nb_philo)
	// 	if (pthread_join(d.philos[id].thread_id, NULL))
	// 		_err("Failed in joining thread.");
	return (0);
}
