/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:57:21 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/16 15:58:48 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->target_meals = ft_atoi(argv[5]);
	else
		table->target_meals = -1;
	table->simulation_end = 0;
	table->philosophers = NULL;
	table->forks = NULL;
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_fork) * table->number_of_philosophers);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->forks[i].fork_id = i;
		if (pthread_mutex_init(&table->forks[i].fork_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	assign_forks(t_philosopher *philo, t_table *table, int i)
{
	philo->left_fork = &table->forks[i];
	philo->right_fork = &table->forks[(i + 1) % table->number_of_philosophers];
}

int	init_philosophers(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher)
			* table->number_of_philosophers);
	if (!table->philosophers)
		return (1);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philosophers[i].philosopher_id = i + 1;
		table->philosophers[i].meals_count = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].table = table;
		assign_forks(&table->philosophers[i], table, i);
		i++;
	}
	return (0);
}
