/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:47:51 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/17 20:25:31 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

long	ft_get_time_ms(t_data *data)
{
	gettimeofday(&data->time, NULL);
	return ((long)(data->time.tv_sec * 1000 + data->time.tv_usec / 1000));
}

void	ft_print_routine(t_data *data, int id, const char *routine)
{
	pthread_mutex_lock(&data->tab_philo[id]->m_alive);
	if (data->is_started)
		printf("%ld %d %s", ft_get_time_ms(data), id+1, routine);
	pthread_mutex_unlock(&data->tab_philo[id]->m_alive);
}
