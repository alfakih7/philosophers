#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>   
# include <stdlib.h>  
# include <pthread.h> 
# include <unistd.h>  
# include <sys/time.h>
#include <stdbool.h>


typedef struct s_philo
{
    pthread_mutex_t meal_mutex;
    int             id;         
    long            start;
    int             philo_num;      
    int             eat_cont;   
    int             status;     
    // int             philo_nums;
    long long last_meal_time; 
    long long       time_to_die; 
    int             meals_nb;       
    struct s_data   *data;
    long long       death_time;     
    long long       eat_time;       
    long long       sleep_time;     
}               t_philo;

typedef struct s_data
{
    pthread_mutex_t meals_eaten_mutex;
    int             philos_finished_eating;
    int             should_stop;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t     isdead_mutex;
    pthread_mutex_t print_mutex;
    int             fforks[200];
    int             philo_num;      
    long long       death_time;     
    long long       eat_time;       
    long long       sleep_time;     
    int             meals_nb;       
    int             is_dead;           
    int             finished;       
    long long       start_time;     
    pthread_t       tid[200];
    t_philo         philos[200];
    pthread_mutex_t forks[200];
}               t_data;
int     init_data(t_data *data, int argc, char **argv);
int     init_mutexes(t_data *data);
int     init_philos(t_data *data);
int	    simulation(t_data *data);
void    *routine(void *arg);
long long   get_time(void);
long long ft_atoi(const char *str , bool *error);
int	ft_usleep(size_t milliseconds , t_philo *philo);
// void is_dead(t_philo *philo);
// void *monitor_routine(void *arg);
int	check_philosopher_death(t_philo *philo);
void print_status(t_philo *philo, const char *status, const char *color);
int try_to_eat(t_philo *philo, int right_fork_id, int left_fork_id);
// int     try_to_eat(t_philo *philo);
int	validate_input(t_data *data, int argc, char **argv);
#endif
