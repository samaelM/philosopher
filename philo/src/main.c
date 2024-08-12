/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/12 16:54:51 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static void	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->tab_fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->is_started_mutex, NULL);
}

static int	ft_check_data(t_data *data)
{
	return (data->nb_philo > 0 && data->time_die > 0 && data->time_eat > 0
		&& data->time_sleep > 0);
}

static int	ft_init(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	ft_memset(data, 0, sizeof(data));
	if (ac == 6)
		data->nb_eat_max = ft_atoi(av[5]);
	else
		data->nb_eat_max = -1;
	data->is_started = 0;
	data->nb_finished = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	if (!ft_check_data(data))
		return (0);
	data->tab_philo = malloc(data->nb_philo * sizeof(t_philo *));
	if (!data->tab_philo)
		return (0);
	data->tab_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->tab_fork)
		return (free(data->tab_philo), 0);
	ft_init_mutex(data);
	return (1);
}

void	ft_free_data(t_data *data)
{
	int	i;

	free(data->tab_fork);
	i = 0;
	while (i < data->nb_philo)
	{
		free(data->tab_philo[i]);
		i++;
	}
	free(data->tab_philo);
}

void ft_unlock_forks(t_data *data)
{
	int i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->tab_fork[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!ft_init(&data, ac, av))
		return (write(2, "Error: problem during init\n", 27), 1);
	ft_create_threads(&data);
	ft_wait_setup(&data);
	ft_wait_death(&data);
	// ft_unlock_forks(&data);
	ft_wait_threads(&data);
	ft_free_data(&data);
	// printf("anaelle fin");
	return (0);
}
