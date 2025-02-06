/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:55:15 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:35:09 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ARGUMENTS:
// number_of_philosophers time_to_die time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat][optional]

// EXTERNAL FUNCTIONS:
// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock

#include "../include/philo.h"


/*
 * The main function of the program.
 * It initializes the data structures, checks for errors in the input arguments,
 * and starts the simulation of the philosophers' dinner.
 *
 * Parameters:
 * - argc: The number of command-line arguments.
 * - argv: The command-line arguments.
 *
 * Returns:
 * - 0 on successful execution.
 * - 1 if there are errors in the input arguments.
 * - 2 if memory allocation for the philosophers' data structure fails.
 * - 3 if memory allocation for the forks' mutexes fails.
 */
int	main(int argc, char **argv)
{
	t_data			data;
	t_philo_params	params;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ft_iferror(argc, argv))
		return (printf("Error: input arguments wrong.\n"), 1);
	init_params(argv, &params);
	philo = malloc(params.num_of_philo * sizeof(t_philo));
	if (philo == NULL)
		return (printf("Error: failed to malloc memory for t_philo struct.\n"),
			2);
	forks = malloc(params.num_of_philo * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (printf("Error: failed to malloc memory for mutex.\n"),
			free(philo), 3);
	data.philo = philo;
	data.params = &params;
	init_start_philo_forks(&data, forks);
	cleanup_philo_and_forks(&data);
	free_memory(philo, forks);
	return (0);
}
