/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:07:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/09 20:07:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	simulation_should_stop(t_table *table)
{
	int	should_stop;

	pthread_mutex_lock(&table->death_mutex);
	should_stop = table->simulation_end;
	pthread_mutex_unlock(&table->death_mutex);
	return (should_stop);
}

int	check_philosopher_death(t_table *table)
{
	int		i;
	long	current_time;
	long	time_since_meal;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->meal_mutex);
		current_time = get_current_time();
		time_since_meal = current_time - table->philosophers[i].last_meal_time;
		pthread_mutex_unlock(&table->meal_mutex);
		if (time_since_meal > table->time_to_die)
		{
			pthread_mutex_lock(&table->death_mutex);
			table->simulation_end = 1;
			pthread_mutex_unlock(&table->death_mutex);
			pthread_mutex_lock(&table->write_mutex);
			printf("%ld %d died\n", time_since_start(table),
				table->philosophers[i].philosopher_id);
			pthread_mutex_unlock(&table->write_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_ate_enough(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->target_meals == -1)
		return (0);
	i = 0;
	all_ate = 1;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->meal_mutex);
		if (table->philosophers[i].meals_count < table->target_meals)
			all_ate = 0;
		pthread_mutex_unlock(&table->meal_mutex);
		if (!all_ate)
			break ;
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->simulation_end = 1;
		pthread_mutex_unlock(&table->death_mutex);
	}
	return (all_ate);
}
