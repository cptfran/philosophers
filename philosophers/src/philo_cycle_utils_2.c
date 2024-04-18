/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:58:13 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:40:46 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Simulates a philosopher picking up their first fork.
 * Locks the mutex for the first fork and prints a message indicating that the philosopher has taken a fork.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	pick_first_fork(t_data *data)
{
	pthread_mutex_lock(data->philo->first_fork);
	printf("%ld %d has taken a fork\n", timestamp(), data->philo->id);
}

/*
 * Simulates a philosopher waiting for their second fork.
 * Unlocks the mutex for the first fork, sleeps for the time it takes for a philosopher to die,
 * then locks the mutex for philosopher death and sets the philosopher as dead.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	wait_for_second_fork(t_data *data)
{
	pthread_mutex_unlock(data->philo->first_fork);
	usleep(data->params->time_to_die);
	printf("%ld %d died\n", timestamp(), data->philo->id);
	pthread_mutex_lock(&data->params->philo_death);
	data->params->philo_dead = 1;
	pthread_mutex_unlock(&data->params->philo_death);
}

/*
 * Simulates a philosopher picking up their second fork.
 * Locks the mutex for the second fork and prints a message indicating that the philosopher has taken a fork.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	pick_second_fork(t_data *data)
{
	pthread_mutex_lock(data->philo->second_fork);
	printf("%ld %d has taken a fork\n", timestamp(), data->philo->id);
}

/*
 * Checks if the time for a philosopher to die has passed.
 * If the elapsed time since the philosopher's last meal is greater than or equal to the time for a philosopher to die,
 * and the philosopher is not already dead, it locks the mutex for philosopher death, sets the philosopher as dead,
 * prints a message indicating that the philosopher has died, unlocks the mutex for philosopher death,
 * and releases the philosopher's forks.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if the time for the philosopher to die has passed.
 * - 0 otherwise.
 */
int	time_to_die_passed(t_data *data)
{
	if ((elapsed_time(data->philo->last_meal_time)) >= data->params->time_to_die
		&& data->params->philo_dead != 1)
	{
		pthread_mutex_lock(&data->params->philo_death);
		data->params->philo_dead = 1;
		printf("%ld %d died\n", timestamp(), data->philo->id);
		pthread_mutex_unlock(&data->params->philo_death);
		philo_release_forks(data);
		return (1);
	}
	return (0);
}

/*
 * Checks if the time for a philosopher to eat is longer than the time for a philosopher to die.
 * If the time for a philosopher to die is less than the time for a philosopher to eat,
 * it sleeps for the time it takes for a philosopher to die and then checks if the time for the philosopher to die has passed.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if the time for the philosopher to eat is longer than the time for the philosopher to die and the time for the philosopher to die has passed.
 * - 0 otherwise.
 */
int	time_to_eat_longer_than_time_to_die(t_data *data)
{
	if (data->params->time_to_die < data->params->time_to_eat)
	{
		usleep(data->params->time_to_die);
		if (time_to_die_passed(data))
			return (1);
	}
	return (0);
}
