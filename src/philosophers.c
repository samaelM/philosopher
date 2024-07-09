/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:59:28 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 18:33:08 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	ft_eat(t_data *data, int idx)
{
	int	left;
	int	right;

	left = idx;
	right = idx + 1;
	if (idx == data->nb_philo - 1)
		right = 0;
	pthread_mutex_lock(&data->tab_fork[left]);
	pthread_mutex_lock(&data->tab_fork[right]);
	data->tab_philo[idx]->last_meal_ms = ft_get_time_ms(data);
	data->tab_philo[idx]->nb_meal++;
	printf("%ud %d is eating\n", ft_get_time_ms(data), idx);
	usleep(data->time_eat);
	pthread_mutex_unlock(&data->tab_fork[left]);
	pthread_mutex_unlock(&data->tab_fork[right]);
	return (1);
}

void	*ft_philo(void *arg)
{
	char	*ret;
	t_data	*data;
	t_philo	*philo;

	data = ((t_ti *)arg)->data;
	philo = data->tab_philo[((t_ti *)arg)->idx];
	philo->id = ((t_ti *)arg)->idx;
	philo->is_alive = 1;
	free(arg);
	philo->is_setup = 1;
	philo->last_meal_ms = ft_get_time_ms(data);
	ft_wait_start(&data->is_started);
	while (data->is_started && philo->is_alive == 1)
	{
		printf("%ud %d is thinking\n", ft_get_time_ms(data), philo->id);
		ft_eat(data, philo->id);
		if (data->nb_eat_max == philo->nb_meal)
		{
			philo->is_alive = -1;
			break ;
		}
		printf("%ud %d is sleeping\n", ft_get_time_ms(data), philo->id);
		usleep(data->time_sleep);
	}
	ret = ft_itoa(philo->id);
	pthread_exit(ret);
}

int	ft_create_threads(t_data *data)
{
	int		i;
	t_ti	*info;

	i = 0;
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
	return (1);
}
