/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:20 by almohame          #+#    #+#             */
/*   Updated: 2024/10/05 09:41:45 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int ft_usleep(size_t milliseconds, t_philo *philo)
{
    size_t start;

    start = get_time();
    while ((get_time() - start) < milliseconds)
    {
        // pthread_mutex_lock(&philo->data->stop_mutex);
        // if (philo->data->should_stop)
        // {
        //     pthread_mutex_unlock(&philo->data->stop_mutex);
        //     return (1);
        //  }
        // pthread_mutex_unlock(&philo->data->stop_mutex);
        usleep(250);
        if (check_philosopher_death(philo))
            return (1);
    }
    return (0);
}

