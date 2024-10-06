/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:50:20 by almohame          #+#    #+#             */
/*   Updated: 2024/10/06 18:50:44 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->philos_finished_eating = 0;
	if (validate_input(data, argc, argv))
		return (1);
	data->should_stop = 0;
	if (init_mutexes(data))
		return (1);
	data->is_dead = 0;
	data->finished = 0;
	i = 0;
	while (i < data->philo_num)
	{
		data->fforks[i] = 0;
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			perror("Failed to initialize mutex");
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meals_eaten_mutex, NULL) != 0)
		return (1);
	return (0);
	if (pthread_mutex_init(&data->meals_eaten_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].eat_cont = 0;
		data->philos[i].status = 0;
		data->philos[i].philo_num = data->philo_num;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].time_to_die = get_time() + data->death_time;
		data->philos[i].meals_nb = data->meals_nb;
		data->philos[i].death_time = data->death_time;
		data->philos[i].eat_time = data->eat_time;
		data->philos[i].sleep_time = data->sleep_time;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
