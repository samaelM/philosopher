/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:59:28 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/26 18:27:16 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	ft_eat(t_data *data, int idx)
{
	t_philo	*philo;

	philo = data->tab_philo[idx];
	if ((philo->id & 1 && philo->nb_meal == 0))
		ft_usleep(data->time_eat / 2);
	// ft_print_routine(data, philo->id, ft_itoa(philo->f_left + 1));
	pthread_mutex_lock(&data->tab_fork[philo->f_left]);
	ft_print_routine(data, idx, "has taken a fork\n");
	// ft_print_routine(data, philo->id, ft_itoa(philo->f_right + 1));
	pthread_mutex_lock(&data->tab_fork[philo->f_right]);
	ft_print_routine(data, idx, "has taken a fork\n");
	pthread_mutex_lock(&philo->philo_m);
	data->tab_philo[idx]->last_meal_ms = gettime();
	data->tab_philo[idx]->nb_meal++;
	pthread_mutex_unlock(&philo->philo_m);
	ft_print_routine(data, idx, "is eating\n");
	ft_usleep(data->time_eat);
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
	pthread_mutex_init(&philo->philo_m, NULL);
	philo->is_alive = 1;
	philo->f_left = philo->id;
	philo->f_right = philo->id + 1;
	if (philo->id == data->nb_philo - 1)
	{
		philo->f_left = 0;
		philo->f_right = philo->id;
	}
	// philo->have_fork = 0;
	free(arg);
	pthread_mutex_lock(&philo->philo_m);
	philo->is_setup = 1;
	philo->last_meal_ms = 0;
	pthread_mutex_unlock(&philo->philo_m);
	return (1);
}

void	*ft_philo(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = ((t_ti *)arg)->data;
	philo = data->tab_philo[((t_ti *)arg)->idx];
	ft_philo_init(arg);
	if (!ft_wait_start(&data->is_started, &data->data_m))
		return (NULL);
	pthread_mutex_lock(&philo->philo_m);
	philo->last_meal_ms = gettime();
	pthread_mutex_unlock(&philo->philo_m);
	while (1)
	{
		pthread_mutex_lock(&data->print_m);
		if (!data->is_started)
		{
			pthread_mutex_unlock(&data->print_m);
			break ;
		}
		pthread_mutex_unlock(&data->print_m);
		ft_print_routine(data, philo->id, "is thinking\n");
		ft_eat(data, philo->id);
		if (data->nb_eat_max == philo->nb_meal)
		{
			// pthread_mutex_lock(&data->print_m);
			// printf("%ld %d WIN\n", gettime(), philo->id+1);
			// pthread_mutex_unlock(&data->print_m);
			pthread_mutex_lock(&data->data_m);
			philo->is_alive = 0;
			data->nb_finished++;
			pthread_mutex_unlock(&data->data_m);
			break ;
		}
		ft_print_routine(data, philo->id, "is sleeping\n");
		ft_usleep(data->time_sleep);
		if (data->nb_philo % 2 == 1)
			ft_usleep(data->time_eat / 2);
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
		if (!data->tab_philo[i])
			return (i);
		ft_memset(data->tab_philo[i], 0, sizeof(t_philo));
		info = malloc(sizeof(t_ti));
		if (!info)
			return (free(info), i); // faire des trucs je crois
		info->data = data;
		info->idx = i;
		data->tab_philo[i]->is_setup = 0;
		if (pthread_create(&data->tab_philo[i]->thid, NULL, ft_philo,
				info) != 0)
		{
			free(info);
			perror("pthread_create() error");
			return (i);
		}
		i++;
	}
	return (-1);
}
