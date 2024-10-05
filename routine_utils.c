/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:01:12 by almohame          #+#    #+#             */
/*   Updated: 2024/10/05 09:50:56 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	check_philosopher_death(t_data *data, int i)
// {
// 	pthread_mutex_lock(&data->philos[i].meal_mutex);
// 	if (get_time() - data->philos[i].last_meal_time >= data->philos[i].death_time)
// 	{
// 		pthread_mutex_unlock(&data->philos[i].meal_mutex);
// 		pthread_mutex_lock(&data->print_mutex);
// 		printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n",
// 			(get_time() - data->start_time), data->philos[i].id);
// 		pthread_mutex_unlock(&data->print_mutex);
// 		pthread_mutex_lock(&data->stop_mutex);
// 		data->should_stop = 1;
// 		pthread_mutex_unlock(&data->stop_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->philos[i].meal_mutex);
// 	return (0);
// }

// static int	check_stop_condition(t_data *data)
// {
// 	pthread_mutex_lock(&data->stop_mutex);
// 	if (data->should_stop)
// 	{
// 		pthread_mutex_unlock(&data->stop_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&data->stop_mutex);
// 	return (0);
// }

// void	*monitor_routine(void *arg)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->philo_num)
// 		{
// 			if (check_philosopher_death(data, i))
// 				return (NULL);
// 			i++;
// 		}
// 		if (check_stop_condition(data))
// 			return (NULL);
// 		usleep(250);
// 	}
// }

void	print_status(t_philo *philo, const char *status, const char *color)
{
    (void) color;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->should_stop)
	{
        //timestamp_in_ms X has taken a fork
		printf("%lld %d %s\n", (get_time() - philo->start), philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}