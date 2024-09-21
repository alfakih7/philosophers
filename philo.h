#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
    pthread_mutex_t *forks;
    int             right_fork_id;
    int             left_fork_id;
    struct s_data   *data;      // Pointer to the main data structure
    pthread_t       t1;         // Thread identifier for this philosopher
    int             id;         // Unique identifier for this philosopher
    int             eat_cont;   // Counter for how many times this philosopher has eaten
    int             status;     // Current status of the philosopher
    int             eating;     // Flag to indicate if the philosopher is currently eating
    uint64_t        time_to_die; // Time left before this philosopher dies if not fed
    pthread_mutex_t lock;       // Mutex for protecting this philosopher's data
    pthread_mutex_t *r_fork;    // Pointer to the right fork's mutex
    pthread_mutex_t *l_fork;    // Pointer to the left fork's mutex
} t_philo;

typedef struct s_data
{
    pthread_t       *tid;       // Array of thread identifiers
    int             philo_num;  // Total number of philosophers
    int             meals_nb;   // Number of times each philosopher must eat (if specified)
    int             dead;       // Flag to indicate if a philosopher has died
    int             finished;   // Flag to indicate if the simulation has finished
    t_philo         *philos;    // Array of philosopher structures
    u_int64_t       death_time; // Time a philosopher can go without eating before dying
    u_int64_t       eat_time;   // Time it takes for a philosopher to eat
    u_int64_t       sleep_time; // Time a philosopher spends sleeping
    u_int64_t       start_time; // Start time of the simulation
    pthread_mutex_t *forks;     // Array of mutexes for forks
    pthread_mutex_t lock;       // General mutex for protecting shared data
    pthread_mutex_t write;      // Mutex for protecting write operations (e.g., printing)
} t_data;

int init_data(t_data *data, int argc, char **argv);
int init_mutexes(t_data *data);
int init_philos(t_data *data);
long long ft_atoi(const char *str);
// void print_status(t_data *data , int id , char *status);
uint64_t get_time(void);
void *routine(void *arg);