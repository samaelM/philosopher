/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:59:28 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/12 17:03:20 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	ft_eat(t_data *data, int idx)
{
	t_philo	*philo;

	philo = data->tab_philo[idx];
	if (philo->id & 1 && philo->nb_meal == 0)
		usleep(data->time_eat / 2);
	pthread_mutex_lock(&data->tab_fork[philo->f_left]);
	ft_print_routine(data, idx, "has taken a fork\n");
	pthread_mutex_lock(&data->tab_fork[philo->f_right]);
	ft_print_routine(data, idx, "has taken a fork\n");
	ft_print_routine(data, idx, "is eating\n");
	pthread_mutex_lock(&data->is_started_mutex);
	data->tab_philo[idx]->last_meal_ms = ft_get_time_ms(data);
	data->tab_philo[idx]->nb_meal++;
	pthread_mutex_unlock(&data->is_started_mutex);
	usleep(data->time_eat);
	pthread_mutex_unlock(&data->tab_fork[philo->f_left]);
	pthread_mutex_unlock(&data->tab_fork[philo->f_right]);
	return (1);
}

static int	ft_philo_init(t_philo *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = ((t_ti *)arg)->data;
	philo = data->tab_philo[((t_ti *)arg)->idx];
	philo->id = ((t_ti *)arg)->idx;
	pthread_mutex_init(&philo->is_alive_m, NULL);
	philo->is_alive = 1;
	philo->f_left = philo->id;
	philo->f_right = philo->id + 1;
	if (philo->id == data->nb_philo - 1)
		philo->f_right = 0;
	philo->have_fork = 0;
	free(arg);
	philo->is_setup = 1;
	philo->last_meal_ms = 0;
	return (1);
}

void	*ft_philo(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = ((t_ti *)arg)->data;
	philo = data->tab_philo[((t_ti *)arg)->idx];
	ft_philo_init(arg);
	ft_wait_start(&data->is_started, &data->is_started_mutex);
	pthread_mutex_lock(&data->is_started_mutex);
	philo->last_meal_ms = ft_get_time_ms(data);
	pthread_mutex_unlock(&data->is_started_mutex);
	// if (philo->id & 1)
	// 	usleep(data->time_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&data->is_started_mutex);
		if (!data->is_started)
		{
			pthread_mutex_unlock(&data->is_started_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->is_started_mutex);
		ft_print_routine(data, philo->id, "is thinking\n");
		ft_eat(data, philo->id);
		if (data->nb_eat_max == philo->nb_meal)
		{
			printf("%ld %d WIN\n", ft_get_time_ms(data), philo->id+1);
			pthread_mutex_lock(&data->is_started_mutex);
			philo->is_alive = 0;
			data->nb_finished++;
			pthread_mutex_unlock(&data->is_started_mutex);
			break ;
		}
		ft_print_routine(data, philo->id, "is sleeping\n");
		usleep(data->time_sleep);
	}
	return (NULL);
}

int	ft_create_threads(t_data *data)
{
	int		i;
	t_ti	*info;

	i = 0;
	while (i < data->nb_philo)
	{
		data->tab_philo[i] = malloc(sizeof(t_philo));
		ft_memset(data->tab_philo[i], 0, sizeof(t_philo));
		info = malloc(sizeof(t_ti));
		info->data = data;
		info->idx = i;
		data->tab_philo[i]->is_setup = 0;
		if (pthread_create(&data->tab_philo[i]->thid, NULL, ft_philo,
				info) != 0)
		{
			perror("pthread_create() error");
			exit(1);
		}
		i++;
	}
	return (1);
}
