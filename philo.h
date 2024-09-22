#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>    // Standard I/O for printing messages.
# include <stdlib.h>   // Standard library for general functions like malloc and free.
# include <pthread.h>  // POSIX threads for creating and managing threads.
# include <unistd.h>   // Unix standard functions like usleep.
# include <sys/time.h> // Time functions to handle timestamps and time calculations.

# define MAX_PHILOS 200  // Maximum number of philosophers allowed in the simulation.

// Struct for holding all the necessary data for each philosopher.
typedef struct s_philo
{
    int             id;          // Philosopher's ID (1-based index).
    int             eat_cont;    // Count of how many times this philosopher has eaten.
    int             status;      // Status of the philosopher (e.g., eating, thinking).
    long long last_meal_time; 
    long long       time_to_die; // Timestamp when the philosopher will die if not fed.
    pthread_mutex_t *l_fork;     // Pointer to the left fork (mutex).
    pthread_mutex_t *r_fork;     // Pointer to the right fork (mutex).
    struct s_data   *data;       // Pointer to the shared data structure.
}               t_philo;

// Struct for holding all the shared data needed for the simulation.
typedef struct s_data
{
    int             philo_num;       // Number of philosophers.
    long long       death_time;      // Time in milliseconds before a philosopher dies without eating.
    long long       eat_time;        // Time in milliseconds a philosopher spends eating.
    long long       sleep_time;      // Time in milliseconds a philosopher spends sleeping.
    int             meals_nb;        // Number of meals each philosopher must have (or -1 for unlimited).
    int             dead;            // Flag indicating if a philosopher has died.
    int             finished;        // Flag indicating if the simulation is finished.
    long long       start_time;      // Timestamp of when the simulation started.
    pthread_t       tid[MAX_PHILOS]; // Array of thread identifiers for each philosopher.
    t_philo         philos[MAX_PHILOS]; // Array of philosopher structures (no dynamic allocation).
    pthread_mutex_t forks[MAX_PHILOS];  // Array of mutexes representing each fork (no dynamic allocation).
}               t_data;

// Function prototypes for the various functionalities in the program.

// Function to initialize the main data structure with input arguments.
int     init_data(t_data *data, int argc, char **argv);

// Function to initialize all the mutexes representing forks.
int     init_mutexes(t_data *data);

// Function to initialize each philosopher's data.
int     init_philos(t_data *data);

// The main simulation function that creates threads and starts the routine.
int     simulation(t_data *data);

// The routine that each philosopher thread executes.
void    *routine(void *arg);

// Function to get the current time in milliseconds.
long long   get_time(void);

// A utility function to safely parse integers from strings.
long long   ft_atoi(const char *str);

int	ft_usleep(size_t milliseconds);
#endif
