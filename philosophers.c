/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:47:34 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/07 11:48:28 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_exit(char *message)
{
	printf("Error: %s\n", message);
	return (1);
}

void	cleanup_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	
	// Destruir mutexes de tenedores
	if (table->forks)
	{
		i = 0;
		while (i < table->number_of_philosophers)
		{
			pthread_mutex_destroy(&table->forks[i].fork_mutex);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	if (table->philosophers)
	{
		free(table->philosophers);
		table->philosophers = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (verify_args(argc, argv) == 1)
		return (1);
	if (init_table(&table, argc, argv) != 0)
		return (error_exit("Failed to initialize table"));
	if (init_forks(&table) != 0)
	{
		cleanup_table(&table);
		return (error_exit("Failed to initialize forks"));
	}
	if (init_philosophers(&table) != 0)
	{
		cleanup_table(&table);
		return (error_exit("Failed to initialize philosophers"));
	}
	start_simulation(&table);
	cleanup_table(&table);
	return (0);
}