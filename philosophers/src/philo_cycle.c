/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:23:56 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:49:45 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * The main cycle of a philosopher's life.
 * Each philosopher alternates between taking forks, eating, releasing forks, sleeping, and thinking.
 * The cycle continues until the philosopher dies or all philosophers have eaten the required number of meals.
 *
 * Parameters:
 * - arg: A pointer to the data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - NULL after freeing the data structure.
 */
void	*philo_cycle(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	get_time_of_last_meal(data);
	if (even_philo(data))
		printf("%ld %d is thinking\n", timestamp(), data->philo->id);
	while (!data->params->philo_dead && !time_to_die_passed(data))
	{
		if (all_philos_ate_needed_num_of_meals(data))
			return (NULL);
		philo_take_forks(data);
		while (!data->params->philo_dead && philo_picked_forks_and_thought(data)
			&& !time_to_die_passed(data))
		{
			philo_eat(data);
			philo_release_forks(data);
		}
		while (!data->params->philo_dead && data->philo->has_eaten
			&& !time_to_die_passed(data))
			philo_sleep(data);
		while (!data->params->philo_dead && data->philo->has_slept
			&& !time_to_die_passed(data))
			philo_think(data);
	}
	return (free(data), NULL);
}

/*
 * Simulates a philosopher taking their forks.
 * The philosopher picks up their first fork, waits for their second fork if they are the only philosopher,
 * then picks up their second fork and sets their state to having picked up two forks.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - NULL.
 */
void	*philo_take_forks(t_data *data)
{
	set_order_for_picking_forks(data);
	pick_first_fork(data);
	if (data->params->num_of_philo == 1)
	{
		wait_for_second_fork(data);
		return (NULL);
	}
	pick_second_fork(data);
	data->philo->picked_2_forks = 1;
	return (NULL);
}

/*
 * Simulates a philosopher eating.
 * If the time for the philosopher to die has passed or the time for the philosopher to eat is longer than the time for the philosopher to die, the function returns.
 * Otherwise, it updates the time of the philosopher's last meal, prints a message indicating that the philosopher is eating,
 * sleeps for the time it takes for a philosopher to eat, increments the number of meals the philosopher has eaten,
 * sets the philosopher to full if they have eaten the required number of meals, and sets the philosopher's state to having eaten.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	philo_eat(t_data *data)
{
	if (time_to_die_passed(data) || time_to_eat_longer_than_time_to_die(data))
		return ;
	get_time_of_last_meal(data);
	printf("%ld %d is eating\n", timestamp(), data->philo->id);
	usleep(data->params->time_to_eat);
	data->philo->num_of_meals++;
	set_philo_to_full_if_ate_needed_num_of_meals(data);
	data->philo->has_thought = 0;
	data->philo->has_eaten = 1;
}

/*
 * Simulates a philosopher releasing their forks.
 * If there is more than one philosopher, it unlocks the mutexes for the philosopher's forks and sets the philosopher's state to not having picked up two forks.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	philo_release_forks(t_data *data)
{
	if (data->params->num_of_philo > 1)
	{
		pthread_mutex_unlock(data->philo->fork_right);
		pthread_mutex_unlock(data->philo->fork_left);
		data->philo->picked_2_forks = 0;
	}
}

/*
 * Simulates a philosopher sleeping.
 * Prints a message indicating that the philosopher is sleeping, checks if the time for the philosopher to die is shorter than the time for the philosopher to eat plus the time for the philosopher to sleep,
 * sleeps for the time it takes for a philosopher to sleep, and sets the philosopher's state to having slept.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	philo_sleep(t_data *data)
{
	printf("%ld %d is sleeping\n", timestamp(), data->philo->id);
	if (time_to_die_shorter_than_time_to_eat_plus_time_to_sleep(data))
		return ;
	usleep(data->params->time_to_sleep);
	data->philo->has_eaten = 0;
	data->philo->has_slept = 1;
}
