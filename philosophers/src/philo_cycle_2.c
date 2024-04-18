/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:20:46 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:37:19 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Simulates a philosopher thinking.
 * If the philosopher is not dead, it prints a message indicating that the philosopher is thinking,
 * then sleeps for a short period of time, and finally updates the philosopher's state.
 *
 * Parameters:
 * - data: The data structure containing the philosopher and their parameters.
 */
void	philo_think(t_data *data)
{
	if (check_death_for_2_philo(data))
		return ;
	printf("%ld %d is thinking\n", timestamp(), data->philo->id);
	usleep(1000);
	data->philo->has_slept = 0;
	data->philo->has_thought = 1;
}
