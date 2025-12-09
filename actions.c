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

#include "philosophers.h"

static void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	print_status(philo, "has taken a fork");
}

static void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	philo_eat(t_philosopher *philo)
{
	int	current_meals;

	pthread_mutex_lock(&philo->table->meal_mutex);
	current_meals = philo->meals_count;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	if (philo->table->target_meals != -1
		&& current_meals >= philo->table->target_meals)
		return ;
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	precise_usleep(philo->table->time_to_eat);
	release_forks(philo);
}

void	philo_sleep(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->table->time_to_sleep);
}

void	philo_think(t_philosopher *philo)
{
	print_status(philo, "is thinking");
}
