/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 11:51:18 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/07 11:51:33 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/* Verifica si un carácter es un dígito */
static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/* Verifica si una cadena contiene solo dígitos */
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	// Permitir signo '+' al inicio (opcional)
	if (str[i] == '+')
		i++;
	// Debe haber al menos un dígito después del signo
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

/* Convierte string a long y verifica overflow */
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
		// Verificar overflow ANTES de multiplicar
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);  // Overflow detectado
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

/* Verifica que el valor esté en rango válido de int positivo */
static int	is_valid_int(char *str)
{
	long	value;

	value = ft_atol(str);
	if (value == -1)  // Overflow
		return (0);
	if (value > INT_MAX)  // Supera INT_MAX
		return (0);
	if (value < 0)  // Negativo
		return (0);
	return (1);
}

/* Función principal de verificación */
int	verify_args(int argc, char **argv)
{
	int		i;
	long	num_philos;

	// Verificar número de argumentos
	if (argc != 5 && argc != 6)
		return (error_exit("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"));
	
	// Verificar que todos sean números válidos y sin overflow
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
