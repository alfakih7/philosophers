/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:01:12 by almohame          #+#    #+#             */
/*   Updated: 2024/09/28 20:36:54 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    while (1)
    {
        for (int i = 0; i < data->philo_num; i++)
        {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            if (get_time() - data->philos[i].last_meal_time >= data->death_time)
            {
                pthread_mutex_unlock(&data->philos[i].meal_mutex);
                pthread_mutex_lock(&data->print_mutex);
                printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n", 
                       (get_time() - data->start_time), data->philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                pthread_mutex_lock(&data->stop_mutex);
                data->should_stop = 1;
                pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
        }
        usleep(1000); // Sleep for 1ms to reduce CPU usage
    }
    return NULL;
}
void print_status(t_philo *philo, const char *status, const char *color)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->stop_mutex);
    if (!philo->data->should_stop)
    {
        printf("%s[%lld ms] Philosopher %d %s\033[0m\n", 
               color, (get_time() - philo->start), philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->stop_mutex);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
