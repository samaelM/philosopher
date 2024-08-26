/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/26 17:35:43 by maemaldo         ###   ########.fr       */
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
	pthread_mutex_init(&data->data_m, NULL);
	pthread_mutex_init(&data->print_m, NULL);
}

static int	ft_nbnb(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]))
			nb++;
		i++;
	}
	return (nb);
}

static int	is_int(char *str, int nb)
{
	if (ft_nbnb(str) > 10)
		return (0);
	if (ft_nbnb(str) == 10 && nb < 1000000000)
		return (0);
	// printf("int ok\n");
	return (1);
}

static int	ft_check_data(t_data *data, char **av)
{
	if (is_int(av[1], data->nb_philo) && is_int(av[2], data->time_die)
		&& is_int(av[3], data->time_eat) && is_int(av[4], data->time_sleep)
		&& data->nb_philo > 0 && data->time_die > 0 && data->time_eat > 0
		&& data->time_sleep > 0)
		return (1);
	return (0);
}

static int	ft_init(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	ft_memset(data, 0, sizeof(data));
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
	// printf("%d\n", ac);
	if (!ft_check_data(data, av))
		return (0);
	data->tab_philo = malloc(data->nb_philo * sizeof(t_philo *));
	if (!data->tab_philo)
		return (0);
	// ft_memset(data->tab_philo, 0, sizeof(t_philo *));
	ft_bzero(data->tab_philo, sizeof(t_philo *)*data->nb_philo);
	data->tab_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->tab_fork)
		return (free(data->tab_philo), 0);
	ft_init_mutex(data);
	return (1);
}

int	ft_free_data(t_data *data)
{
	int	i;

	if (data->tab_fork)
		free(data->tab_fork);
	i = 0;
	while (data->tab_philo && i < data->nb_philo)
	{
		if (data->tab_philo[i])
			free(data->tab_philo[i]);
		i++;
	}
	if (data->tab_philo)
		free(data->tab_philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (!ft_init(&data, ac, av))
		return (write(2, "Error: problem during init\n", 27), 1);
	i = ft_create_threads(&data);
	if (i != -1)
	{
		pthread_mutex_lock(&data.data_m);
		data.is_started = -1;
		pthread_mutex_unlock(&data.data_m);
		return (ft_wait_threads(&data, i), ft_free_data(&data));
	}
	ft_wait_setup(&data);
	ft_wait_death(&data);
	ft_wait_threads(&data, data.nb_philo);
	ft_free_data(&data);
	return (0);
}
