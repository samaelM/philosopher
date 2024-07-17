/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:43:17 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/17 18:54:43 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	ft_wait_setup(t_data *data)
{
	int	i;
	int	nb_ok;

	i = 0;
	nb_ok = 0;
	while (nb_ok < data->nb_philo)
	{
		if (data->tab_philo[i]->is_setup == 1)
		{
			data->tab_philo[i]->is_setup = 2;
			nb_ok++;
		}
		if (i >= data->nb_philo - 1)
			i = 0;
		else
			i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->tab_philo[i]->last_meal_ms = ft_get_time_ms(data);
		i++;
	}
	data->is_started = 1;
}

void	ft_wait_start(int *start)
{
	while (*start == 0)
		;
}

void	ft_wait_death(t_data *data)
{
	int	i;

	i = 0;
	while (data->is_started)
	{
		if (data->tab_philo[i]->is_alive == 1)
			break ;
		else if (ft_get_time_ms(data)
			- data->tab_philo[i]->last_meal_ms >= data->time_die)
		{
			pthread_mutex_lock(&data->tab_philo[i]->m_alive);
			data->tab_philo[i]->is_alive = 0;
			printf("%ld %d died diff = %li\n", ft_get_time_ms(data), i,
				ft_get_time_ms(data) - data->tab_philo[i]->last_meal_ms);
			if (data->tab_philo[i]->have_fork && printf("unlock fork %d\n",
					data->tab_philo[i]->id))
				pthread_mutex_unlock(&data->tab_fork[data->tab_philo[i]->f_left]);
			pthread_mutex_unlock(&data->tab_fork[data->tab_philo[i]->f_right]);
			pthread_mutex_unlock(&data->tab_philo[i]->m_alive);
			data->is_started = 0;
		}
		if (i == data->nb_philo - 1)
			i = 0;
		else
			i++;
	}
}

void	ft_wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->tab_philo[i]->thid, NULL) != 0)
		{
			perror("pthread_create() error");
			exit(3);
		}
		i++;
	}
}
