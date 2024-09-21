/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:58 by almohame          #+#    #+#             */
/*   Updated: 2024/09/21 18:57:07 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_data(t_data *data, int argc, char **argv)
{
    data->philo_num = ft_atoi(argv[1]);
    data->death_time = ft_atoi(argv[2]);
    data->eat_time = ft_atoi(argv[3]);
    data->sleep_time = ft_atoi(argv[4]);
    if(argc == 6)
        data->meals_nb = ft_atoi(argv[5]);
    else
        data->meals_nb = -1;
    data->dead = 0;
    data->finished = 0;
}

int init_mutexes(t_data *data)
{
   int i = 0;
   data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
   if(!data->forks)
        return 1;
   while(i < data->philo_num)
   {
        if(pthread_mutex_init(&data->forks[i] , NULL) != 0)
        {
            perror("fail to init the mutex");
            return 1;
        }
        i++;
   }
   return (0);
}

int init_philos(t_data *data)
{
    int i = 0;
    data->philos = malloc(sizeof(t_philo *) * data->philo_num);
    if(!data->philos)
        return 1;
    i = 0;
    while(i < data->philo_num)
    {
        data->philos[i].data = data;
        data->philos[i].id = i + 1;
        data->philos[i].eat_cont = 0;
        data->philos[i].status = 0;
        data->philos[i].eat_cont = 0;
        data->philos[i].time_to_die = get_time() + data->death_time;
        data->philos[i].l_fork = &data->forks[i];
        data->philos[i].r_fork = &data->forks[(i + 1) % data->philo_num];
        i++;
    }
    return (0);
}
