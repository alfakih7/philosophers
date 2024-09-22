#include "philo.h"

int simulation(t_data *data)
{
    int i;
    data->start_time = get_time();
    for (i = 0; i < data->philo_num; i++)
    {
        if (pthread_create(&data->tid[i], NULL, routine, &data->philos[i]) != 0)
            return 1;
    }
    
    for (i = 0; i < data->philo_num; i++)
    {
        pthread_join(data->tid[i], NULL);
    }
    return 0;
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int right_fork_id = philo->id - 1;
    int left_fork_id = philo->id % philo->data->philo_num;

    while (1)
    {
        if(philo->data->philo_num == 1)
        {
            printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n", get_time(), philo->id);
            pthread_exit(NULL);
        }
        if (get_time() - philo->last_meal_time > philo->time_to_die)
        {
            printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n", get_time(), philo->id);
            pthread_exit(NULL);
        }
        pthread_mutex_lock(&philo->data->forks[right_fork_id]);
        pthread_mutex_lock(&philo->data->forks[left_fork_id]);
        printf("\033[33m[%lld ms] 💪 Philosopher %d has taken the right fork! 🥄\033[0m\n", get_time(), philo->id);
        printf("👐 \033[31m[%lld ms]\033[0m Philosopher %d has taken the left fork! 🥄\n", get_time(), philo->id);
        printf("🍽️ \033[32m[%lld ms]\033[0m Philosopher %d is eating! 😋\n", get_time(), philo->id);
        usleep(philo->data->eat_time);
        philo->eat_cont++;
         if (philo->eat_cont == philo->data->meals_nb)
        {
            printf("Philosopher %d has eaten %d times.\n", philo->id, philo->eat_cont);
            pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
            pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
        pthread_mutex_unlock(&philo->data->forks[left_fork_id]);

        printf("😴 \033[33m[%lld ms]\033[0m Philosopher %d is sleeping... 💤\n", get_time(), philo->id);
        ft_usleep(philo->data->sleep_time);

        printf("🤔 \033[34m[%lld ms]\033[0m Philosopher %d is thinking... 💭\n", get_time(), philo->id);
        ft_usleep(philo->data->sleep_time);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    
    if (init_data(&data, argc, argv))
        return 1;

    if (init_mutexes(&data))
        return 1;

    if (init_philos(&data))
        return 1;

    if (simulation(&data))
        return 1;

    for (int i = 0; i < data.philo_num; i++)
    {
        pthread_mutex_destroy(&data.forks[i]);
    }

    return 0;
}
