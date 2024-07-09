/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 18:06:39 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"
// #include <string.h>
// #include <unistd.h>

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
	int		i;
	void	*ret;
	t_ti	*info;

	data = ft_init(ac, av);
	if (!data)
		return (1);
	i = 0;
	data->is_started = 0;
	while (i < data->nb_philo)
	{
		data->tab_philo[i] = malloc(sizeof(t_philo));
		data->tab_philo[i]->nb_meal = 0;
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
	gettimeofday(&data->time, NULL);
	i = 0;
	printf("----------------start--------------\n");
	ft_wait_setup(data);
	data->is_started = 1;
	ft_wait_death(data);
	while (i < data->nb_philo)
	{
		if (pthread_join(data->tab_philo[i]->thid, &ret) != 0)
		{
			perror("pthread_create() error");
			exit(3);
		}
		printf("thread exited with '%s'\n", (char *)ret);
		i++;
	}
	data->is_started = 0;
	return (0);
}
