/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:10:26 by sfrankie          #+#    #+#             */
/*   Updated: 2024/04/18 12:36:07 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * Checks if the number of arguments and their validity.
 *
 * Parameters:
 * - argc: The number of command-line arguments.
 * - argv: The command-line arguments.
 *
 * Returns:
 * - 0 if the number of arguments is correct and all arguments are valid.
 * - 1 otherwise.
 */
int	ft_iferror(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (!ft_ifdigitarr(argv + 1))
		return (1);
	return (0);
}

/*
 * Checks if a string is a valid positive integer.
 *
 * Parameters:
 * - argv: The string to check.
 *
 * Returns:
 * - 1 if the string is a valid positive integer.
 * - 0 otherwise.
 */
int	ft_ifdigitstr(char *argv)
{
	if (!*argv || *argv == '0')
		return (0);
	while (*argv)
	{
		if (ft_is_plus_digit(*argv) || *argv == ' ')
			argv++;
		else
			return (0);
	}
	return (1);
}

/*
 * Checks if an array of strings are all valid positive integers.
 *
 * Parameters:
 * - argv: The array of strings to check.
 *
 * Returns:
 * - 1 if all strings in the array are valid positive integers.
 * - 0 otherwise.
 */
int	ft_ifdigitarr(char **argv)
{
	while (*argv)
	{
		if (!ft_ifdigitstr(*argv++))
			return (0);
	}
	return (1);
}

/*
 * Checks if a character is a digit.
 *
 * Parameters:
 * - i: The character to check.
 *
 * Returns:
 * - 1 if the character is a digit.
 * - 0 otherwise.
 */
int	ft_is_plus_digit(int i)
{
	if (i <= '9' && i >= '0')
		return (1);
	return (0);
}
