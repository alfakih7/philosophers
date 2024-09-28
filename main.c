#include "philo.h"


int simulation(t_data *data)
{
    int i;
    pthread_t monitor_tid;

    data->start_time = get_time();
    data->should_stop = 0;
    

    i = 0;
    while (i < data->philo_num)
    {
        if (pthread_create(&data->tid[i], NULL, routine, &data->philos[i]) != 0)
            return 1;
        i++;
    }
    
    if (pthread_create(&monitor_tid, NULL, monitor_routine, data) != 0)
        return 1;

    pthread_join(monitor_tid, NULL);

    pthread_mutex_lock(&data->stop_mutex);
    data->should_stop = 1;
    pthread_mutex_unlock(&data->stop_mutex);
    i = 0;
    while (i < data->philo_num)
    {
        pthread_join(data->tid[i], NULL);
        i++;
    }

    return 0;
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    philo->start = get_time();
    int right_fork_id = philo->id - 1;
    int left_fork_id = philo->id % philo->data->philo_num;

    while (1)
    {
        pthread_mutex_lock(&philo->data->stop_mutex);
        if (philo->data->should_stop)
        {
            pthread_mutex_unlock(&philo->data->stop_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->stop_mutex);

        if (philo->data->philo_num == 1)
        {
            print_status(philo, "has taken the right fork", "\033[33m");
            ft_usleep(philo->data->death_time, philo);
            break;
        }

        if (try_to_eat(philo, right_fork_id, left_fork_id))
        {
            print_status(philo, "is sleeping", "\033[33m");
            ft_usleep(philo->data->sleep_time, philo);
            print_status(philo, "is thinking", "\033[34m");
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    t_data data;
    int i;
    i = 0;

    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo number_of_philosophers data->death_time time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
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

    while (i < data.philo_num)
    {
        pthread_mutex_destroy(&data.forks[i]);
        i++;
    }
    return 0;
}
