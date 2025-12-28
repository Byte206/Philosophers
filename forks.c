/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by byte              #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by byte             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_single_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	print_status(philo, "has taken a fork");
	while (!simulation_should_stop(philo->table))
		usleep(1000);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	return (0);
}

static void	get_forks_order(t_philosopher *philo, t_fork **first,
			t_fork **second)
{
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static int	lock_fork(t_philosopher *philo, t_fork *fork, t_fork *other)
{
	pthread_mutex_lock(&fork->fork_mutex);
	if (simulation_should_stop(philo->table))
	{
		pthread_mutex_unlock(&fork->fork_mutex);
		if (other)
			pthread_mutex_unlock(&other->fork_mutex);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

int	take_forks(t_philosopher *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->table->number_of_philosophers == 1)
		return (wait_single_philo(philo));
	get_forks_order(philo, &first, &second);
	if (!lock_fork(philo, first, NULL))
		return (0);
	if (simulation_should_stop(philo->table))
	{
		pthread_mutex_unlock(&first->fork_mutex);
		return (0);
	}
	if (!lock_fork(philo, second, first))
		return (0);
	return (1);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}
