/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:28:55 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:45:10 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Updates the time of the philosopher's last meal to the current time.
 * If getting the current time fails, the function returns without updating the time.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	get_time_of_last_meal(t_data *data)
{
	if (gettimeofday(&data->philo->last_meal_time, NULL) != 0)
		return ;
}

/*
 * Checks if a philosopher is even.
 * If the philosopher's ID minus 1 is not divisible by 2, the philosopher is considered even.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if the philosopher is even.
 * - 0 otherwise.
 */
int	even_philo(t_data *data)
{
	if ((data->philo->id - 1) % 2 != 0)
		return (1);
	return (0);
}

/*
 * Checks if all philosophers have eaten the required number of meals.
 * If the required number of meals is not zero and the number of full philosophers is equal to the number of philosophers,
 * it unlocks the mutex for full philosophers, frees the data structure, and returns 1.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if all philosophers have eaten the required number of meals.
 * - 0 otherwise.
 */
int	all_philos_ate_needed_num_of_meals(t_data *data)
{
	pthread_mutex_lock(&data->params->full_philos_mutex);
	if (data->params->needed_meals != 0
		&& data->params->full_philos == data->params->num_of_philo)
	{
		pthread_mutex_unlock(&data->params->full_philos_mutex);
		free(data);
		return (1);
	}
	pthread_mutex_unlock(&data->params->full_philos_mutex);
	return (0);
}

/*
 * Checks if a philosopher has picked up two forks and thought.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 *
 * Returns:
 * - 1 if the philosopher has picked up two forks and thought.
 * - 0 otherwise.
 */
int	philo_picked_forks_and_thought(t_data *data)
{
	if (data->philo->picked_2_forks && data->philo->has_thought)
		return (1);
	return (0);
}

/*
 * Sets the order for a philosopher to pick up their forks.
 * If the philosopher's ID is even, they pick up their right fork first and then their left fork.
 * If the philosopher's ID is odd, they pick up their left fork first and then their right fork.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	set_order_for_picking_forks(t_data *data)
{
	if (data->philo->id % 2 == 0)
	{
		data->philo->first_fork = data->philo->fork_right;
		data->philo->second_fork = data->philo->fork_left;
	}
	else
	{
		data->philo->first_fork = data->philo->fork_left;
		data->philo->second_fork = data->philo->fork_right;
	}
}
