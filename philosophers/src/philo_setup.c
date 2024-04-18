/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:07:42 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:51:21 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Initializes the parameters for the philosophers from the command line arguments.
 * Converts the command line arguments to integers and assigns them to the appropriate parameters.
 * Initializes the mutexes for the number of full philosophers and philosopher death.
 *
 * Parameters:
 * - argv: The command line arguments.
 * - params: The structure to store the parameters.
 */
void	init_params(char **argv, t_philo_params *params)
{
	params->num_of_philo = atoi(argv[1]);
	params->time_to_die = atoi(argv[2]) * 1000;
	params->time_to_eat = atoi(argv[3]) * 1000;
	params->time_to_sleep = atoi(argv[4]) * 1000;
	if (argv[5] != NULL)
		params->needed_meals = atoi(argv[5]);
	else
		params->needed_meals = 0;
	params->full_philos = 0;
	if (pthread_mutex_init(&params->full_philos_mutex, NULL) != 0)
	{
		printf("Error initializing mutex.\n");
		return ;
	}
	params->philo_dead = 0;
	if (pthread_mutex_init(&params->philo_death, NULL) != 0)
	{
		printf("Error initializing mutex.\n");
		return ;
	}
}

/*
 * Initializes the philosophers and their forks and starts the philosophers' life cycles.
 *
 * Parameters:
 * - data: The data structure containing the philosophers and their parameters.
 * - forks: The array of mutexes for the forks.
 */
void	init_start_philo_forks(t_data *data, pthread_mutex_t *forks)
{
	init_philo_and_forks(data, forks);
	start_philo(data);
}

/*
 * Initializes the philosophers and their forks.
 * Assigns each philosopher an ID and two forks, and initializes the mutexes for the forks.
 *
 * Parameters:
 * - data: The data structure containing the philosophers and their parameters.
 * - forks: The array of mutexes for the forks.
 */
void	init_philo_and_forks(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->params->num_of_philo)
	{
		init_args(&data->philo[i]);
		data->philo[i].id = i + 1;
		data->philo[i].fork_right = &forks[i];
		data->philo[i].fork_left = &forks[(i + data->params->num_of_philo - 1)
			% data->params->num_of_philo];
		i++;
	}
	i = 0;
	while (i < data->params->num_of_philo)
	{
		if (pthread_mutex_init(data->philo[i].fork_left, NULL) != 0
			|| pthread_mutex_init(data->philo[i].fork_right, NULL) != 0)
		{
			printf("Error initializing mutexes.\n");
			return ;
		}
		i++;
	}
}

/*
 * Initializes the arguments for a philosopher.
 * Sets the philosopher's state to not full, not dead, not having picked up two forks, not having eaten, not having slept, and having thought.
 *
 * Parameters:
 * - philo: The philosopher to initialize the arguments for.
 */
void	init_args(t_philo *philo)
{
	philo->is_full = 0;
	philo->is_dead = 0;
	philo->picked_2_forks = 0;
	philo->num_of_meals = 0;
	philo->has_eaten = 0;
	philo->has_slept = 0;
	philo->has_thought = 1;
	philo->is_full = 0;
	philo->is_dead = 0;
	philo->picked_2_forks = 0;
}

/*
 * Starts the philosophers' life cycles.
 * Creates a new thread for each philosopher and starts their life cycle in the thread.
 *
 * Parameters:
 * - data: The data structure containing the philosophers and their parameters.
 */
void	start_philo(t_data *data)
{
	t_data	*thread_data;
	int		i;

	i = 0;
	while (i < data->params->num_of_philo)
	{
		thread_data = malloc(sizeof(t_data));
		if (!thread_data)
		{
			printf("Error allocating memory for thread.\n");
			return ;
		}
		thread_data->philo = &data->philo[i];
		thread_data->params = data->params;
		pthread_create(&data->philo[i].thread, NULL, philo_cycle, thread_data);
		i++;
	}
}
