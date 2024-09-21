#include "philo.h"  // Include the header file that contains necessary function declarations and data structures.

// simulation.c
#include "philo.h"

int simulation(t_data *data)
{
    int i;
    // No need to allocate memory for tid since it's a static array.
    data->start_time = get_time(); // Get the start time of the simulation.
    for (i = 0; i < data->philo_num; i++) // Create a thread for each philosopher.
    {
        if (pthread_create(&data->tid[i], NULL, routine, &data->philos[i]) != 0)
            return 1; // Return error if thread creation fails.
    }
    
    for (i = 0; i < data->philo_num; i++) // Join all philosopher threads.
    {
        pthread_join(data->tid[i], NULL);
    }
    return 0; // Return success.
}


void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;  // Cast the argument to a philosopher pointer.
    int right_fork_id = philo->id - 1;  // Calculate the right fork ID (index).
    int left_fork_id = philo->id % philo->data->philo_num;  // Calculate the left fork ID (next index, wrapping around).

    while (1)  // Infinite loop for philosopher routine.
    {
        pthread_mutex_lock(&philo->data->forks[right_fork_id]);  // Lock the right fork.
        printf("Philosopher %d has taken the right fork\n", philo->id);
        pthread_mutex_unlock(&philo->data->forks[right_fork_id]);

        pthread_mutex_lock(&philo->data->forks[left_fork_id]);  // Lock the left fork.
        printf(" %lld Philosopher %d has taken the left fork\n", get_time() ,philo->id);
        pthread_mutex_unlock(&philo->data->forks[left_fork_id]);

        printf(" %lld Philosopher %d is eating\n", get_time(),philo->id);
        usleep(philo->data->eat_time * 1000);  // Simulate eating time (in microseconds).
        // pthread_mutex_unlock(&philo->data->forks[right_fork_id]);  // Unlock the right fork.
        // pthread_mutex_unlock(&philo->data->forks[left_fork_id]);  // Unlock the left fork.

        printf("Philosopher %d is thinking\n", philo->id);
        usleep(philo->data->sleep_time * 1000);  // Simulate thinking time (in microseconds).
    }

    return NULL;  // Return NULL to indicate the end of the routine.
}


int main(int argc, char **argv)
{
    t_data data;  // Declare the main data structure that holds all information about the simulation.

    // Check if the number of arguments is correct.
    if (argc != 5 && argc != 6)
    {
        // If not, print usage instructions and exit.
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    
    // Initialize the data structure with command line arguments.
    if (init_data(&data, argc, argv))
        return 1;  // Return 1 if initialization fails.

    // Initialize the mutexes for the forks.
    if (init_mutexes(&data))
        return 1;  // Return 1 if mutex initialization fails.

    // Initialize the philosophers.
    if (init_philos(&data))
        return 1;  // Return 1 if philosopher initialization fails.

    // Start the simulation.
    if (simulation(&data))
        return 1;  // Return 1 if the simulation fails.

    // Destroy each mutex after the simulation ends to release resources.
    for (int i = 0; i < data.philo_num; i++)
    {
        pthread_mutex_destroy(&data.forks[i]);  // Destroy each mutex.
    }

    return 0;  // Return 0 to indicate the program finished successfully.
}
