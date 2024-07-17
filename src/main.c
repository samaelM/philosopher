/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/17 18:42:17 by maemaldo         ###   ########.fr       */
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
}

static t_data	*ft_init(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (NULL);
	if (ac == 6)
		data->nb_eat_max = ft_atoi(av[5]);
	else
		data->nb_eat_max = -1;
	data->is_started = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	data->tab_philo = malloc(data->nb_philo * sizeof(t_philo *));
	if (!data->tab_philo)
		return (NULL);
	data->tab_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->tab_fork)
		return (free(data->tab_philo), NULL);
	ft_init_mutex(data);
	return (data);
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

int	main(int ac, char **av)
{
	t_data	data;

	ft_init(&data, ac, av);
	ft_create_threads(&data);
	ft_wait_setup(&data);
	ft_wait_death(&data);
	ft_wait_threads(&data);
	ft_free_data(&data);
	return (0);
}
