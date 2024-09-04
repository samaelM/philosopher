/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/04 19:10:18 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	ft_nbnb(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb++;
		i++;
	}
	return (nb);
}

int	is_int(char *str, int nb)
{
	if (ft_nbnb(str) > 10)
		return (0);
	if (ft_nbnb(str) == 10 && nb < 1000000000)
		return (0);
	if (ft_is_neg(str))
		return (0);
	return (1);
}

int	ft_check_data(t_data *data, char **av)
{
	if (is_int(av[1], data->nb_philo) && is_int(av[2], data->time_die)
		&& is_int(av[3], data->time_eat) && is_int(av[4], data->time_sleep)
		&& data->nb_philo > 0 && data->time_die > 0 && data->time_eat > 0
		&& data->time_sleep > 0)
		return (1);
	return (0);
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
