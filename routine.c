/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:32:40 by almohame          #+#    #+#             */
/*   Updated: 2024/10/06 19:03:18 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_single_philo(t_philo *philo)
{
	print_status(philo, "has taken the right fork", "\033[33m");
	ft_usleep(philo->data->death_time, philo);
	return (1);
}

static void	philosopher_actions(t_philo *philo, int right_fork_id,
		int left_fork_id)
{
	if (try_to_eat(philo, right_fork_id, left_fork_id))
	{
		print_status(philo, "is sleeping", "\033[33m");
		ft_usleep(philo->data->sleep_time, philo);
		print_status(philo, "is thinking", "\033[34m");
	}
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
	left_fork_id = philo->id % philo->data->philo_num;
	// pthread_mutex_unlock(&philo->data->num_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->should_stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		// pthread_mutex_lock(&philo->data->num_mutex);
		if (philo->data->philo_num == 1 && handle_single_philo(philo))
			break ;
		// pthread_mutex_unlock(&philo->data->num_mutex);
		philosopher_actions(philo, right_fork_id, left_fork_id);
	}
	return (NULL);
}