/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:16:02 by tlemesle          #+#    #+#             */
/*   Updated: 2021/10/14 14:03:19 by tlemesle         ###   ########.fr       */
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
	start_simulation(&d);
	return (0);
}
