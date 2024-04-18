/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:12:58 by sfrankie          #+#    #+#             */
/*   Updated: 2024/02/15 16:59:26 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo_params
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				needed_meals;
	int				full_philos;
	pthread_mutex_t	full_philos_mutex;
	int				philo_dead;
	pthread_mutex_t	philo_death;
}	t_philo_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	struct timeval	last_meal_time;
	int				num_of_meals;
	int				has_eaten;
	int				has_slept;
	int				has_thought;
	int				is_dead;
	int				is_full;
	int				picked_2_forks;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}	t_philo;

typedef struct s_data
{
	t_philo_params	*params;
	t_philo			*philo;
}	t_data;

// ERROR MANAGEMENT (error.c)
int		ft_iferror(int argc, char **argv);
int		ft_ifdigitstr(char *argv);
int		ft_ifdigitarr(char **argv);
int		ft_is_plus_digit(int i);

// PHILO SETUP (philo_setup.c)
void	init_params(char **argv, t_philo_params *params);
void	init_start_philo_forks(t_data *data, pthread_mutex_t *forks);
void	init_philo_and_forks(t_data *data, pthread_mutex_t *forks);
void	init_args(t_philo *philo);
void	start_philo(t_data *data);

// PHILO CYCLE (philo_cycle.c, philo_cycle_2.c)
void	*philo_cycle(void *arg);
void	*philo_take_forks(t_data *data);
void	philo_eat(t_data *data);
void	philo_release_forks(t_data *data);
void	philo_sleep(t_data *data);
void	philo_think(t_data *data);

// MAIN UTILS (main_utils.c)
void	free_memory(t_philo *philo, pthread_mutex_t *mutex);
void	cleanup_philo_and_forks(t_data *data);

// PHILO CYCLE UTILS (philo_cycle_utils.c, philo_cycle_utils_2.c)
void	get_time_of_last_meal(t_data *data);
int		even_philo(t_data *data);
int		all_philos_ate_needed_num_of_meals(t_data *data);
int		philo_picked_forks_and_thought(t_data *data);
void	set_order_for_picking_forks(t_data *data);
void	pick_first_fork(t_data *data);
void	wait_for_second_fork(t_data *data);
void	pick_second_fork(t_data *data);
int		time_to_die_passed(t_data *data);
int		time_to_eat_longer_than_time_to_die(t_data *data);
void	set_philo_to_full_if_ate_needed_num_of_meals(t_data *data);
long	elapsed_time(struct timeval last_meal_time);
long	timestamp(void);
int		time_to_die_shorter_than_time_to_eat_plus_time_to_sleep(t_data *data);
int		check_death_for_2_philo(t_data *data);

#endif