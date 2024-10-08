/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:43:17 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/04 19:09:51 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"
#include <pthread.h>

void	ft_wait_setup(t_data *data)
{
	int	i;
	int	nb_ok;

	i = 0;
	nb_ok = 0;
	while (1)
	{
		usleep(1);
		pthread_mutex_lock(&data->data_m);
		if (nb_ok >= data->nb_philo)
			break ;
		pthread_mutex_unlock(&data->data_m);
		pthread_mutex_lock(&data->tab_philo[i]->philo_m);
		if (data->tab_philo[i]->is_setup == 1)
		{
			data->tab_philo[i]->is_setup = 2;
			nb_ok++;
		}
		pthread_mutex_unlock(&data->tab_philo[i]->philo_m);
		i = (i + 1) % data->nb_philo;
	}
	data->is_started = 1;
	pthread_mutex_unlock(&data->data_m);
}

int	ft_wait_start(int *start, pthread_mutex_t *start_m)
{
	while (1)
	{
		usleep(1);
		pthread_mutex_lock(start_m);
		if (*start == 1)
		{
			pthread_mutex_unlock(start_m);
			return (1);
		}
		if (*start == -1)
		{
			pthread_mutex_unlock(start_m);
			return (0);
		}
		pthread_mutex_unlock(start_m);
	}
}

void	ft_wait_death(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(1);
		pthread_mutex_lock(&data->data_m);
		if (!data->is_started || data->nb_finished == data->nb_philo)
			break ;
		pthread_mutex_unlock(&data->data_m);
		pthread_mutex_lock(&data->tab_philo[i]->philo_m);
		if (gettime() - data->tab_philo[i]->last_meal_ms >= data->time_die
			&& data->tab_philo[i]->last_meal_ms != 0
			&& data->tab_philo[i]->is_alive)
		{
			pthread_mutex_lock(&data->print_m);
			data->is_started = 0;
			printf("%ld %d %s", gettime(), i + 1, "died\n");
			pthread_mutex_unlock(&data->print_m);
		}
		pthread_mutex_unlock(&data->tab_philo[i]->philo_m);
		i = (i + 1) % data->nb_philo;
	}
	pthread_mutex_unlock(&data->data_m);
}

void	ft_wait_threads(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		usleep(1);
		if (data->tab_philo[i] && pthread_join(data->tab_philo[i]->thid,
				NULL) != 0)
		{
			perror("pthread_create() error");
			exit(3);
		}
		i++;
	}
}

int	ft_is_neg(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (1);
	return (0);
}
