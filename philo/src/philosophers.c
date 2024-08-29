/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:59:28 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/29 15:35:50 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	ft_eat(t_data *data, int idx)
{
	t_philo	*philo;

	philo = data->tab_philo[idx];
	if ((philo->id & 1 && philo->nb_meal == 0))
		ft_usleep(data->time_eat / 2);
	pthread_mutex_lock(&data->tab_fork[philo->f_left]);
	ft_print_routine(data, idx, "has taken a fork\n");
	if (data->nb_philo == 1)
	{
		ft_usleep(data->time_die);
		pthread_mutex_unlock(&data->tab_fork[philo->f_left]);
		return (1);
	}
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

void	ft_sleep(t_data *data, t_philo *philo)
{
	ft_print_routine(data, philo->id, "is sleeping\n");
	ft_usleep(data->time_sleep);
	if (data->nb_philo % 2 == 1)
		ft_usleep(data->time_eat / 2);
}

int	ft_is_started(t_data *data)
{
	pthread_mutex_lock(&data->print_m);
	if (!data->is_started)
	{
		pthread_mutex_unlock(&data->print_m);
		return (0);
	}
	pthread_mutex_unlock(&data->print_m);
	return (1);
}

int	ft_check_meal(t_data *data, t_philo *philo)
{
	if (data->nb_eat_max == philo->nb_meal)
	{
		pthread_mutex_lock(&data->data_m);
		philo->is_alive = 0;
		data->nb_finished++;
		pthread_mutex_unlock(&data->data_m);
		return (0);
	}
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
		if (!ft_is_started(data))
			break ;
		ft_print_routine(data, philo->id, "is thinking\n");
		ft_eat(data, philo->id);
		if (!ft_check_meal(data, philo))
			break ;
		ft_sleep(data, philo);
	}
	return (NULL);
}
