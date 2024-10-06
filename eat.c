/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:14:30 by almohame          #+#    #+#             */
/*   Updated: 2024/10/06 15:36:22 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_stop_condition(t_philo *philo, int right_fork_id,
				int left_fork_id)
{
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->should_stop)
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
		pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (0);
}

static void	update_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals_eaten_mutex);
	philo->data->philos_finished_eating++;
	if (philo->data->philos_finished_eating == philo->data->philo_num)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->should_stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->meals_eaten_mutex);
}

static void	perform_eating(t_philo *philo)
{
	print_status(philo, "has taken the right fork", "\033[33m");
	print_status(philo, "has taken the left fork", "\033[31m");
	print_status(philo, "is eating", "\033[32m");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->eat_time, philo);
	philo->eat_cont++;
	if (philo->data->meals_nb != -1 && philo->eat_cont == philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("\033[35mPhilosopher %d has eaten %d times.\033[0m\n",
			philo->id, philo->eat_cont);
		pthread_mutex_unlock(&philo->data->print_mutex);
		update_meal_count(philo);
	}
}

int	try_to_eat(t_philo *philo, int right_fork_id, int left_fork_id)
{
	pthread_mutex_lock(&philo->data->forks[right_fork_id]);
	pthread_mutex_lock(&philo->data->forks[left_fork_id]);
	if (check_stop_condition(philo, right_fork_id, left_fork_id))
		return (0);
	if (philo->data->fforks[left_fork_id] == 0
		&& philo->data->fforks[right_fork_id] == 0)
	{
		philo->data->fforks[right_fork_id] = 1;
		philo->data->fforks[left_fork_id] = 1;
		perform_eating(philo);
		philo->data->fforks[right_fork_id] = 0;
		philo->data->fforks[left_fork_id] = 0;
		pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
		pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
	return (0);
}
