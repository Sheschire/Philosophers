/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:13:19 by tlemesle          #+#    #+#             */
/*   Updated: 2021/11/16 15:37:32 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>

struct				s_data;

typedef struct s_philo
{
	int				id;
	int				nb_meal;
	int				l_fork_id;
	int				r_fork_id;
	unsigned int	start_time;
	unsigned int	last_meal;
	pthread_mutex_t	lock_meal;
	pthread_t		thread_id;
	pthread_t		monitor;
	struct s_data	*d;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_start;
	int				nb_to_eat;
	int				g_nb_meal;
	int				everyone_alive;
	t_philo			*philos;
	pthread_mutex_t	update_nb_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	prompt;
	pthread_mutex_t	check_end;
}					t_data;

// SIMULATION
void			start_simulation(t_data *d);
void			end_simulation(t_data *d);
void			prompt(t_data *d, int id, char *s);

// SIMULATION UTILS
void			update_nb_meal(t_data *d, t_philo *philo);
int				check_end_philo(t_data *d);
int				check_end_monitor(t_data *d, t_philo *philo);

// INIT
void			init_data(t_data *d, char **av);
void			init_philos(t_data *d);

// UTILS
int				check_arg(int ac, char **av);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			_err(char *s);
void			_putstr(char *s);
unsigned int	get_time(void);
unsigned int	time_since_beginning(t_philo *philo);
void			print_debug(t_data *d);
void			usleep_opti(unsigned int ms_time);
int				ft_strcmp(const char *s1, const char *s2);

#endif
