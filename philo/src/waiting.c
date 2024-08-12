/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:43:17 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/12 19:27:35 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	ft_wait_setup(t_data *data)
{
	// ⚠️ mettre des mutex
	int	i;
	int	nb_ok;

	i = 0;
	nb_ok = 0;
	while (nb_ok < data->nb_philo)
	{
		if (data->tab_philo[i]->is_setup == 1)
		{
			data->tab_philo[i]->is_setup = 2;
			nb_ok++;
		}
		if (i >= data->nb_philo - 1)
			i = 0;
		else
			i++;
	}
	pthread_mutex_lock(&data->is_started_mutex);
	data->is_started = 1;
	pthread_mutex_unlock(&data->is_started_mutex);
}

void	ft_wait_start(int *start, pthread_mutex_t *start_m)
{
	while (1)
	{
		pthread_mutex_lock(start_m);
		if (*start == 1)
		{
			pthread_mutex_unlock(start_m);
			break ;
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
		pthread_mutex_lock(&data->is_started_mutex);
		if (!data->is_started || data->nb_finished == data->nb_philo)
		{
			pthread_mutex_unlock(&data->is_started_mutex);
			break ;
		}
		if (ft_get_time_ms(data)
			- data->tab_philo[i]->last_meal_ms >= data->time_die
			&& data->tab_philo[i]->last_meal_ms != 0 && data->tab_philo[i]->is_alive)
		{
			// printf("lm = %ld\n", data->tab_philo[i]->last_meal_ms);
			// printf("diff = %ld\n", ft_get_time_ms(data)
				// - data->tab_philo[i]->last_meal_ms);
			// ft_print_routine(data, i, "died\n");
			printf("%ld %d died\n", ft_get_time_ms(data), i+1);
			// pthread_mutex_lock(&data->is_started_mutex);
			data->is_started = 0;
			// pthread_mutex_unlock(&data->is_started_mutex);
		}
		pthread_mutex_unlock(&data->is_started_mutex);
		if (i == data->nb_philo - 1)
			i = 0;
		else
			i++;
	}
	// printf("anaelle mort fin\n");
}

void	ft_wait_threads(t_data *data)
{
	int	i;

	i = 0;
	// printf("anaelle debut thread\n");
	while (i < data->nb_philo)
	{
		// printf("anaelle thread\n");
		if (pthread_join(data->tab_philo[i]->thid, NULL) != 0)
		{
			perror("pthread_create() error");
			exit(3);
		}
		// printf("anaelle thread success\n");
		i++;
	}
	// printf("anaelle fin thread\n");
}
