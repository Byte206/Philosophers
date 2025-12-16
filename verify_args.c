/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:57:06 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/16 16:03:28 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static int	is_valid_int(char *str)
{
	long	value;

	value = ft_atol(str);
	if (value == -1)
		return (0);
	if (value > INT_MAX)
		return (0);
	if (value < 0)
		return (0);
	return (1);
}

int	verify_args(int argc, char **argv)
{
	int		i;
	long	num_philos;

	if (argc != 5 && argc != 6)
		return (error_exit("Usage: ./philo number_of_philo time_to_die "
				"time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]"));
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (error_exit("Arguments must be positive numbers"));
		if (!is_valid_int(argv[i]))
			return (error_exit("Argument overflow or out of range"));
		i++;
	}
	num_philos = ft_atol(argv[1]);
	if (num_philos < 1 || num_philos > 200)
		return (error_exit("Number of philosophers must be between 1 and 200"));
	if (ft_atol(argv[2]) == 0 || ft_atol(argv[3]) == 0 || ft_atol(argv[4]) == 0)
		return (error_exit("Time values must be greater than 0"));
	return (0);
}
