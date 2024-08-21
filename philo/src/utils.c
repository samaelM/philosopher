/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:47:51 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/21 14:12:08 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

long	ft_get_time_ms(t_data *data)
{
	gettimeofday(&data->time, NULL);
	return ((long)(data->time.tv_sec * 1000 + data->time.tv_usec / 1000));
}
long int	gettime(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	ft_print_routine(t_data *data, int id, const char *routine)
{
	// pthread_mutex_lock(&data->tab_philo[id]->is_alive_m);
	pthread_mutex_lock(&data->is_started_mutex);
	if (data->is_started)
		printf("%ld %d %s", gettime(), id + 1, routine);
	pthread_mutex_unlock(&data->is_started_mutex);
	// pthread_mutex_unlock(&data->tab_philo[id]->is_alive_m);
}

int	ft_usleep(unsigned int time)
{
	long	start;

	start = gettime();
	while ((gettime() - start) < time)
		usleep(time * 10);
	return (0);
}
int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}
int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}