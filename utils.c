/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:20 by almohame          #+#    #+#             */
/*   Updated: 2024/09/27 19:58:07 by almohame         ###   ########.fr       */
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
         // check if dead or not 
        if (philo->data->is_dead)
            return (1);
        usleep(500);
    }
    return (0);
}