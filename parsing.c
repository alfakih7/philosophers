/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:55:21 by almohame          #+#    #+#             */
/*   Updated: 2024/10/06 19:06:00 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str, bool *error)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if ((*str && *str > '9') || *str < 0)
	{
		*error = true;
		return (0);
	}
	return (result * sign);
}

int	validate_input(t_data *data, int argc, char **argv)
{
	bool	error;

	error = false;
	data->philo_num = ft_atoi(argv[1], &error);
	data->death_time = ft_atoi(argv[2], &error);
	data->eat_time = ft_atoi(argv[3], &error);
	data->sleep_time = ft_atoi(argv[4], &error);
	if (error == true)
	{
		printf("Arguments should contain valid digits\n");
		return (1);
	}
	if (data->philo_num < 1 || data->philo_num > 200)
		return (printf("Philosopher numbers must be between 1 and 200\n"), 1);
	if (argc == 6)
	{
		data->meals_nb = ft_atoi(argv[5], &error);
		if (data->meals_nb < 1)
			return (printf("meals numbers should be more than 0\n"), 1);
	}
	else
		data->meals_nb = -1;
	return (0);
}
