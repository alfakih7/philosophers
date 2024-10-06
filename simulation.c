/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 03:04:19 by almohame          #+#    #+#             */
/*   Updated: 2024/10/06 19:06:29 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_tid;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor_tid, NULL, monitor_routine, data) != 0)
		return (1);
	pthread_join(monitor_tid, NULL);
	return (0);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->tid[i], NULL);
		i++;
	}
	return (0);
}

int	simulation(t_data *data)
{
	data->start_time = get_time();
	data->should_stop = 0;
	if (create_threads(data))
		return (1);
	pthread_mutex_lock(&data->stop_mutex);
	data->should_stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	join_threads(data);
	return (0);
}
