/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:25:22 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/29 16:10:02 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->tab_fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->data_m, NULL);
	pthread_mutex_init(&data->print_m, NULL);
}

int	ft_init_values(t_data *data, int ac, char **av)
{
	if (ac == 6)
	{
		data->nb_eat_max = ft_atoi(av[5]);
		if ((!is_int(av[5], data->nb_eat_max) || data->nb_eat_max <= 0))
			return (0);
	}
	else
		data->nb_eat_max = -1;
	data->is_started = 0;
	data->nb_finished = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	return (ft_check_data(data, av));
}

int	ft_init(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	memset(data, 0, sizeof(t_data));
	if (!ft_init_values(data, ac, av))
		return (0);
	data->tab_philo = malloc(data->nb_philo * sizeof(t_philo *));
	if (!data->tab_philo)
		return (0);
	memset(data->tab_philo, 0, sizeof(t_philo *) * data->nb_philo);
	data->tab_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->tab_fork)
		return (free(data->tab_philo), 0);
	ft_init_mutex(data);
	return (1);
}

int	ft_philo_init(t_philo *arg)
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
	free(arg);
	pthread_mutex_lock(&philo->philo_m);
	philo->is_setup = 1;
	philo->last_meal_ms = 0;
	pthread_mutex_unlock(&philo->philo_m);
	return (1);
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
		memset(data->tab_philo[i], 0, sizeof(t_philo));
		info = malloc(sizeof(t_ti));
		if (!info)
			return (free(info), i);
		info->data = data;
		info->idx = i;
		data->tab_philo[i]->is_setup = 0;
		if (pthread_create(&data->tab_philo[i]->thid, NULL, ft_philo,
				info) != 0)
		{
			free(info);
			return (i);
		}
		i++;
	}
	return (-1);
}
