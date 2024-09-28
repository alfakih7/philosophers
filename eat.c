/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:14:30 by almohame          #+#    #+#             */
/*   Updated: 2024/09/28 20:37:18 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int try_to_eat(t_philo *philo, int right_fork_id, int left_fork_id)
{
    pthread_mutex_lock(&philo->data->forks[right_fork_id]);
    pthread_mutex_lock(&philo->data->forks[left_fork_id]);

    pthread_mutex_lock(&philo->data->stop_mutex);
    int should_stop = philo->data->should_stop;
    pthread_mutex_unlock(&philo->data->stop_mutex);

    if (should_stop)
    {
        pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
        pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
        return 0;
    }
    
    if (philo->data->fforks[left_fork_id] == 0 && philo->data->fforks[right_fork_id] == 0)
    {
        philo->data->fforks[right_fork_id] = 1;
        philo->data->fforks[left_fork_id] = 1;

        print_status(philo, "has taken the right fork", "\033[33m");
        print_status(philo, "has taken the left fork", "\033[31m");
        print_status(philo, "is eating", "\033[32m");

        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal_time = get_time();
        pthread_mutex_unlock(&philo->meal_mutex);
        
        ft_usleep(philo->data->eat_time, philo);

        philo->eat_cont++;
        if (philo->eat_cont == philo->data->meals_nb)
        {
            printf("Philosopher %d has eaten %d times.\n", philo->id, philo->eat_cont);
            pthread_mutex_lock(&philo->data->stop_mutex);
            philo->data->should_stop = 1;
            pthread_mutex_unlock(&philo->data->stop_mutex);
        }

        philo->data->fforks[right_fork_id] = 0;
        philo->data->fforks[left_fork_id] = 0;

        pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
        pthread_mutex_unlock(&philo->data->forks[left_fork_id]);

        return 1;
    }

    pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
    pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
    return 0;
}