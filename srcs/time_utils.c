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

unsigned int	get_time(void)
{
	struct timeval	s_time;
	unsigned int	time;

	time = (unsigned int)gettimeofday(&s_time, NULL);
	time = (unsigned int)s_time.tv_sec * 1000 \
	+ (unsigned int)s_time.tv_usec / 1000;
	return (time);
}

unsigned int	time_since_beginning(t_philo *philo)
{
	return (get_time() - philo->start_time);
}

void	usleep_opti(unsigned int ms_time)
{
	unsigned int	start;

	start = 0;
	start = get_time();
	while ((get_time() - start) < ms_time)
		usleep(ms_time / 10);
}
