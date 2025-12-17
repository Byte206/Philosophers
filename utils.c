/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:05:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/09 20:05:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_since_start(t_table *table)
{
	return (get_current_time() - table->sim_start_time);
}

void	precise_usleep(long microseconds, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_current_time();
	while (1)
	{
		if (table && simulation_should_stop(table))
			break ;
		elapsed = get_current_time() - start;
		remaining = microseconds - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 1000)
			usleep(500);
		else
			usleep(100);
	}
}

void	print_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!simulation_should_stop(philo->table))
		printf("%ld %d %s\n", time_since_start(philo->table),
			philo->philosopher_id, status);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
