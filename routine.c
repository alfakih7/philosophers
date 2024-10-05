/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:32:40 by almohame          #+#    #+#             */
/*   Updated: 2024/10/05 09:56:55 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_single_philo(t_philo *philo)
{
	print_status(philo, "has taken the right fork", "\033[33m");
	ft_usleep(philo->death_time, philo);
	return (1);
}

static void	philosopher_actions(t_philo *philo, int right_fork_id,
		int left_fork_id)
{
	if (try_to_eat(philo, right_fork_id, left_fork_id))
	{
		print_status(philo, "is sleeping", "\033[33m");
		ft_usleep(philo->sleep_time, philo);
		print_status(philo, "is thinking", "\033[34m");
	}
}

int	check_philosopher_death(t_philo *philo)
{
    
    pthread_mutex_lock(&philo->data->stop_mutex);
    if (philo->data->should_stop)
    {
        pthread_mutex_unlock(&philo->data->stop_mutex);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->stop_mutex);
	if (get_time() - philo->last_meal_time >= philo->death_time)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n",
			(get_time() - philo->data->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->should_stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		right_fork_id;
	int		left_fork_id;

	philo = (t_philo *)arg;
	philo->start = get_time();
	right_fork_id = philo->id - 1;
	// pthread_mutex_lock(&philo->data->num_mutex);
	left_fork_id = philo->id % philo->philo_num;
	// pthread_mutex_unlock(&philo->data->num_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->should_stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			return (NULL) ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		// pthread_mutex_lock(&philo->data->num_mutex);
		if (philo->philo_num == 1 && handle_single_philo(philo))
			break ;
		// pthread_mutex_unlock(&philo->data->num_mutex);
		philosopher_actions(philo, right_fork_id, left_fork_id);
	}
	return (NULL);
}
