// Step 1: Checking the input
// The first thing we are going to do it checking the input that we recive. As first thing let's take a analyze a standard input that we are going to recive: 5 800 200 200 7
// 5: is the number of philos
// 800: is the time a philosopher must fast to die
// 200: is the time a philosopher takes to eat
// 200: is the time a philosopher takes to sleep
// 7: are the times all the philos must eat in or

#include "philo.h"

// void *philo_routine(void *arg)
// {

// }

// int start_simulation(t_data *data)
// {

// }
// void assign_forks(t_philo *philo , int num_philos)
// {
//     philo->right_fork_id = philo->id;
//     philo->left_fork_id = (philo->id + 1) % num_philos;
// }

void *routine(void *arg)
{
    // int i = 0;
    // int fork = i * 2;
    t_philo *philo = (t_philo *)arg;
    int right_fork_id = philo->right_fork_id;
    int left_fork_id = philo->left_fork_id;;

    while (1)
    {
        pthread_mutex_lock(&philo->forks[right_fork_id]);
        printf("thread %llu  %d has taken the right fork\n", get_time() ,philo->id);
        pthread_mutex_unlock(&philo->forks[left_fork_id]);
        pthread_mutex_lock(&philo->forks[left_fork_id]);
        printf("thread %d has taken the left fork\n" , philo->id);
        printf("thread %d is eating\n", philo->id);
        sleep(1);
       
        // pthread_mutex_unlock(&philo->forks[right_fork_id]);
        printf("threads %d is thinking\n ", philo->id);
        sleep(1);
        printf("threads %d is sleeping \n ", philo->id);
        sleep(1);
    }
    // printf("thread %d has started eating\n" , thread_id);
    return NULL;
}

int main(int argc, char **argv)
{
    t_data data;
    if(argc != 5 && argc != 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    if(init_data(&data , argc , argv))
        return 1;
    if(init_mutexes(&data))
        return 1;
    if(init_philos(&data))
        return 1;
    if(start_simulation(&data))
        return 1;
    // (void)argc;
    // int num_philosphers;
    // int i;
    // i = 0;

    // num_philosphers = atoi(argv[1]);
    // pthread_t th[num_philosphers];
    // t_philo philosophers[num_philosphers];
    // t_data data;
    // data.philo_num = num_philosphers;
    // data.forks = malloc(sizeof(pthread_mutex_t) * num_philosphers);
    // // pthread_mutex_t forks[num_philosphers];

    // while (i < num_philosphers)
    // {
    //     if (pthread_mutex_init(&data.forks[i], NULL) != 0)
    //     {
    //         perror("failed to init the mutexes");
    //         return 1;
    //     }
    //     i++;
    // }
    // i = 0;
    // while (i < num_philosphers)
    // {
    //     philosophers[i].id = i;
    //     philosophers[i].forks = data.forks;
    //     philosophers[i].left_fork_id = i;
    //     philosophers[i].right_fork_id = (i + 1) % num_philosphers;
    //     philosophers[i].forks = data.forks;
    //     philosophers[i].data = &data;
    //     if (pthread_create(&th[i], NULL, &routine, &philosophers[i]) != 0)
    //     {
    //         perror("failed to create a thread");
    //         return 1;
    //     }
    //     // printf("thread %d started eating\n" , i);
    //     i++;
    // }
    // i = 0;
    // while (i < num_philosphers)
    // {
    //     if (pthread_join(th[i], NULL) != 0)
    //     {
    //         return 2;
    //     }
    //     // pthread_mutex_unlock(&mutex);
    //     i++;
    // }
    // i = 0;
    // while (i < num_philosphers)
    // {
    //     pthread_mutex_destroy(&data.forks[i]);
    //     i++;
    // }
    // free(data.forks);
    return(0);
}