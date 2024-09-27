#include "philo.h"

int simulation(t_data *data)
{
    int i;
    data->start_time = get_time();
    i = 0;
    while (i < data->philo_num)
    {
        if (pthread_create(&data->tid[i], NULL, routine, &data->philos[i]) != 0)
            return 1;
        i++;
    }
    i = 0;
    while (i < data->philo_num)
    {
        pthread_join(data->tid[i], NULL);
        i++;
    }
    return 0;
}

void is_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->isdead_mutex);
    if (get_time() - philo->last_meal_time >= philo->data->death_time && philo->data->is_dead == 0)
    {
        printf("h\n");
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n", (get_time() - philo->start), philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        pthread_mutex_unlock(&philo->data->isdead_mutex);
        philo->data->is_dead = 1;
        exit(0);
    }
    pthread_mutex_unlock(&philo->data->isdead_mutex);
   
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    philo->start = get_time();
    int right_fork_id = philo->id - 1;
    int left_fork_id = philo->id % philo->data->philo_num;

    while (1)
    {

        if(philo->data->philo_num == 1)
        {
            printf("\033[33m[%lld ms] 💪 Philosopher %d has taken the right fork! 🥄\033[0m\n", (get_time() - philo->start), philo->id);
            ft_usleep(philo->data->death_time, philo);
            printf("\033[31m[%lld ms] 😵 Philosopher %d has died! 💀\033[0m\n", (get_time() - philo->start), philo->id);
            exit(1);
        }
        pthread_mutex_lock(&philo->data->forks[right_fork_id]);
        pthread_mutex_lock(&philo->data->forks[left_fork_id]);
        if(philo->data->fforks[left_fork_id] == 0 && philo->data->fforks[right_fork_id] == 0)
        {
            is_dead(philo);
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("\033[33m[%lld ms] 💪 Philosopher %d has taken the right fork! 🥄\033[0m\n", (get_time() - philo->start), philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
            is_dead(philo);
            philo->data->fforks[right_fork_id] = 1;
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("👐 \033[31m[%lld ms]\033[0m Philosopher %d has taken the left fork! 🥄\n", (get_time() - philo->start), philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
            is_dead(philo);
            philo->data->fforks[left_fork_id] = 1;
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("🍽️ \033[32m[%lld ms]\033[0m Philosopher %d is eating! 😋\n", (get_time() - philo->start), philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
            is_dead(philo);
            pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
            pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
            ft_usleep(philo->data->eat_time, philo);
            philo->last_meal_time = get_time();
            pthread_mutex_lock(&philo->data->forks[right_fork_id]);
            pthread_mutex_lock(&philo->data->forks[left_fork_id]);
            philo->data->fforks[right_fork_id] = 0;
            philo->data->fforks[left_fork_id] = 0;
            philo->eat_cont++;
            if (philo->eat_cont == philo->data->meals_nb)
            {
                printf("Philosopher %d has eaten %d times.\n", philo->id, philo->eat_cont);
                pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
                pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
                exit(1);
            }
            pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
            pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
            is_dead(philo);    
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("😴 \033[33m[%lld ms]\033[0m Philosopher %d is sleeping... 💤\n", (get_time() - philo->start), philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
            is_dead(philo);
            ft_usleep(philo->data->sleep_time , philo);
            pthread_mutex_lock(&philo->data->print_mutex);
            printf("🤔 \033[34m[%lld ms]\033[0m Philosopher %d is thinking... 💭\n", (get_time() - philo->start), philo->id);
            pthread_mutex_unlock(&philo->data->print_mutex);
        }
        else
        {
            pthread_mutex_unlock(&philo->data->forks[right_fork_id]);
            pthread_mutex_unlock(&philo->data->forks[left_fork_id]);
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
