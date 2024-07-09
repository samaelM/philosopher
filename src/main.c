/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 18:30:09 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static t_data	*ft_init(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (ac < 5 || ac > 6)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (ac == 6)
		data->nb_eat_max = ft_atoi(av[5]);
	else
		data->nb_eat_max = -1;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	data->tab_philo = malloc(data->nb_philo * sizeof(t_philo *));
	data->is_started = 0;
	data->tab_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->tab_fork[i], NULL);
		i++;
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_init(ac, av);
	if (!data)
		return (1);
	data->is_started = 0;
	ft_create_threads(data);
	gettimeofday(&data->time, NULL);
	printf("----------------start--------------\n");
	ft_wait_setup(data);
	data->is_started = 1;
	ft_wait_death(data);
	ft_wait_threads(data);
	data->is_started = 0;
	return (0);
}
