/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:15:19 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:42:38 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Sets a philosopher to full if they have eaten the required number of meals.
 * If the philosopher has eaten the required number of meals and is not already full,
 * it sets the philosopher to full, locks the mutex for full philosophers,
 * increments the number of full philosophers, and unlocks the mutex for full philosophers.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	set_philo_to_full_if_ate_needed_num_of_meals(t_data *data)
{
	if (data->params->needed_meals != 0
		&& data->philo->num_of_meals == data->params->needed_meals
		&& !data->philo->is_full)
	{
		data->philo->is_full = 1;
		pthread_mutex_lock(&data->params->full_philos_mutex);
		data->params->full_philos++;
		pthread_mutex_unlock(&data->params->full_philos_mutex);
	}
}

/*
 * Calculates the elapsed time since a given time.
 *
 * Parameters:
 * - last_meal_time: The time to calculate the elapsed time from.
 *
 * Returns:
 * - The elapsed time in microseconds.
 * - -1 if getting the current time fails.
 */
long	elapsed_time(struct timeval last_meal_time)
{
	struct timeval	current_time;
	long			elapsed_time_in_microsec;

	if (gettimeofday(&current_time, NULL) != 0)
		return (-1);
	elapsed_time_in_microsec = (current_time.tv_sec * 1000000
			+ current_time.tv_usec)
		- (last_meal_time.tv_sec * 1000000 + last_meal_time.tv_usec);
	return (elapsed_time_in_microsec);
}

/*
 * Gets the current timestamp.
 *
 * Returns:
 * - The current timestamp in milliseconds.
 * - -1 if getting the current time fails.
 * - -2 if the calculated timestamp is negative.
 */
long	timestamp(void)
{
	struct timeval	current_time;
	long			time_in_milisec;

	if (gettimeofday(&current_time, NULL) != 0)
		return (-1);
	time_in_milisec = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (time_in_milisec < 0)
		return (-2);
	return (time_in_milisec);
}

/*
 * Checks if the time for a philosopher to die is shorter than the time for a philosopher to eat plus the time for a philosopher to sleep.
 * If the time for a philosopher to die is less than the time for a philosopher to eat plus the time for a philosopher to sleep,
 * it sleeps for the time it takes for a philosopher to die minus the elapsed time since the philosopher's last meal,
 * and then checks if the time for the philosopher to die has passed.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if the time for the philosopher to die is shorter than the time for the philosopher to eat plus the time for the philosopher to sleep and the time for the philosopher to die has passed.
 * - 0 otherwise.
 */
int	time_to_die_shorter_than_time_to_eat_plus_time_to_sleep(t_data *data)
{
	if (data->params->time_to_die < data->params->time_to_eat
		+ data->params->time_to_sleep)
	{
		usleep(data->params->time_to_die
			- elapsed_time(data->philo->last_meal_time));
		if (time_to_die_passed(data))
			return (1);
	}
	return (0);
}

/*
 * Checks if a philosopher is dead for a scenario with 2 philosophers.
 * If the difference between the time for a philosopher to die and the sum of the time for a philosopher to eat and the time for a philosopher to sleep is less than 100,
 * and there are 2 philosophers, it sleeps for the time difference, and then checks if the time for the philosopher to die has passed.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if the philosopher is dead.
 * - 0 otherwise.
 */
int	check_death_for_2_philo(t_data *data)
{
	long	time_diff;

	time_diff = (data->params->time_to_die - (data->params->time_to_eat
				+ data->params->time_to_sleep)) / 1000;
	if ((time_diff < 100) && data->params->num_of_philo == 2)
	{
		usleep(time_diff * 1000);
		if (time_to_die_passed(data))
			return (1);
	}
	return (0);
}
