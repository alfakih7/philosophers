#include "philo.h"

// Initialize the main data structure with input arguments.
int init_data(t_data *data, int argc, char **argv)
{
    // Parse the number of philosophers from the arguments and store it in the data structure.
    data->philo_num = ft_atoi(argv[1]);
    // Parse the time a philosopher can live without eating (time to die).
    data->death_time = ft_atoi(argv[2]);
    // Parse the time a philosopher spends eating.
    data->eat_time = ft_atoi(argv[3]);
    // Parse the time a philosopher spends sleeping.
    data->sleep_time = ft_atoi(argv[4]);

    // If there is a 6th argument, parse it as the number of meals required.
    if (argc == 6)
        data->meals_nb = ft_atoi(argv[5]);
    else
        data->meals_nb = -1; // Set to -1 if not specified, meaning unlimited.

    data->dead = 0; // No philosopher is dead initially.
    data->finished = 0; // Simulation is not finished initially.
    return 0;
}

// Initialize all the mutexes representing forks.
int init_mutexes(t_data *data)
{
    int i = 0;
    // Loop through each philosopher and initialize a mutex for each fork.
    while (i < data->philo_num)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) // Initialize fork mutex.
        {
            perror("Failed to initialize mutex");
            return 1; // Return error if mutex initialization fails.
        }
        i++;
    }
    return 0;
}

// Initialize each philosopher's data.
int init_philos(t_data *data)
{
    int i = 0;
    // Loop through each philosopher to set their properties.
    while (i < data->philo_num)
    {
        data->philos[i].data = data; // Assign the shared data structure.
        data->philos[i].id = i + 1; // Set philosopher's ID (1-based index).
        data->philos[i].eat_cont = 0; // Initialize eating count.
        data->philos[i].status = 0; // Initialize status (e.g., eating, thinking).
        data->philos[i].time_to_die = get_time() + data->death_time; // Set initial time to die.
        // Set left and right forks using static array indices.
        data->philos[i].l_fork = &data->forks[i];
        data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_num];
        i++;
    }
    return 0;
}
