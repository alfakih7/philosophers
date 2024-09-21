/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:55:21 by almohame          #+#    #+#             */
/*   Updated: 2024/09/21 17:54:42 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long ft_atoi(const char *str)
{
    int sign;
    long long result;
    sign = 1;
    result = 0;
    while(*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if(*str == '-')
        sign = -1;
    if(*str == '-' || *str == '+')
        str++;
    while(*str >= '0' && *str <= '9'){
        result = result * 10 + *str - '0';
        str++;
    }
    if((*str && *str > '9') || *str < 0)
        return(9999999999999);
    return (result * sign);
}
