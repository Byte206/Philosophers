/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:06:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/09 20:06:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philosopher *philo)
{
	int	current_meals;

	if (simulation_should_stop(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->meal_mutex);
	current_meals = philo->meals_count;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (philo->table->target_meals != -1
		&& current_meals >= philo->table->target_meals)
		return ;
	if (!take_forks(philo))
		return ;
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_status(philo, "is eating");
	precise_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	release_forks(philo);
}

void	philo_sleep(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philosopher *philo)
{
	print_status(philo, "is thinking");
	if (philo->table->number_of_philosophers % 2 != 0)
		usleep(100);
}
