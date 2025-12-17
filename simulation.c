/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:03:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/16 15:59:07 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_table *table)
{
	int	i;

	table->sim_start_time = get_current_time();
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philosophers[i].last_meal_time = table->sim_start_time;
		if (pthread_create(&table->philosophers[i].thread_id, NULL,
				philosopher_routine, &table->philosophers[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL,
			monitor_routine, table) != 0)
		return ;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(table->philosophers[i].thread_id, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->philosopher_id % 2 == 0)
		precise_usleep(philo->table->time_to_eat / 2);
	while (!simulation_should_stop(philo->table))
	{
		if (simulation_should_stop(philo->table))
			break ;
		philo_eat(philo);
		if (simulation_should_stop(philo->table))
			break ;
		philo_sleep(philo);
		if (simulation_should_stop(philo->table))
			break ;
		philo_think(philo);
		if (simulation_should_stop(philo->table))
			break ;
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!simulation_should_stop(table))
	{
		if (check_philosopher_death(table))
			break ;
		if (check_all_ate_enough(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
