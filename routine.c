/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 23:01:12 by almohame          #+#    #+#             */
/*   Updated: 2024/09/21 19:04:52 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_status(t_data *data , int id , char *status)
// {
//     pthread_mutex_lock(&data->write);
//     if(!data->stop)
//         printf("%lld %d %s\n" , get_time() - data->start_time , id , status);
//     pthread_mutex_unlock(&data->write);
// }
int simulation (t_data *data)
{
    int i;
    data->tid = malloc(sizeof(pthread_t) * data->philo_num);
    if(!data->tid)
        return 1;
    data->start_time = get_time();
    i = 0;
    while(i < data->philo_num)
    {
        if(pthread_create(&data->tid[i] , NULL , routine, &data->philos[i]))
            return 1;
        i++;
    }
    i = 0;
    while(i < data->philo_num)
    {
        if(pthread_join(data->tid , NULL)!= 0)
            return 2;
        i++;
    }
}