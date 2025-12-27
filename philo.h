/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:35:39 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/18 09:43:41 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/* ====== CONSTANTS ====== */

# define MAX_THINK_TIME_MS 1

/* ====== STRUCTURES ====== */

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				fork_id;
}					t_fork;

typedef struct s_philosopher
{
	int				philosopher_id;
	int				meals_count;
	long			last_meal_time;		// Timestamp de última comida
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_table			*table;				// Referencia a la mesa
}					t_philosopher;

typedef struct s_table
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				target_meals;		// -1 si no hay límite
	long			sim_start_time;		// Timestamp inicio simulación
	int				simulation_end;		// Flag: simulación terminada
	pthread_t		monitor_thread;		// Hilo monitor
	pthread_mutex_t	write_mutex;		// Protege printf
	pthread_mutex_t	meal_mutex;			// Protege last_meal_time y meals_count
	pthread_mutex_t	death_mutex;		// Protege simulation_end
	t_philosopher	*philosophers;
	t_fork			*forks;
}					t_table;

/* ====== FUNCTION PROTOTYPES ====== */

// Initialization
int		init_table(t_table *table, int argc, char **argv);
int		init_forks(t_table *table);
int		init_philosophers(t_table *table);
int		verify_args(int argc, char **argv);

// Simulation
void	start_simulation(t_table *table);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

// Actions
void	philo_eat(t_philosopher *philo);
void	philo_sleep(t_philosopher *philo);
void	philo_think(t_philosopher *philo);

// Utils - Time
long	get_current_time(void);
void	precise_usleep(long milliseconds, t_table *table);
long	time_since_start(t_table *table);

// Utils - Monitor
int		check_philosopher_death(t_table *table);
int		check_all_ate_enough(t_table *table);
int		simulation_should_stop(t_table *table);

// Utils - Print
void	print_status(t_philosopher *philo, char *status);

// Cleanup
void	cleanup_table(t_table *table);
void	destroy_mutexes(t_table *table);

// Error handling
int		error_exit(char *message);

#endif