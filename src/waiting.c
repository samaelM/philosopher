/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:43:17 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 18:02:22 by maemaldo         ###   ########.fr       */
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
}

void	ft_wait_start(int *start)
{
	while (*start == 0)
		;
}

void	ft_wait_death(t_data *data)
{
	int	i;
	int	nb_dead;

	i = 0;
	nb_dead = 0;
	while (data->is_started && nb_dead < data->nb_philo)
	{
		if (data->tab_philo[i]->is_alive == -1)
		{
			data->tab_philo[i]->is_alive = 0;
			nb_dead++;
		}
		if (data->tab_philo[i]->is_alive == 1 && ft_get_time_ms(data)
			- data->tab_philo[i]->last_meal_ms >= data->time_die)
		{
			data->tab_philo[i]->is_alive = 0;
			nb_dead++;
			printf("moooooooort%d\n", i);
				// regarde si tout les philo sont en vie,
				// doit contenir un mutex pour dieu sais quel raison
		}
		if (i == data->nb_philo - 1)
			i = 0;
		else
			i++;
	}
	printf("ayoooooooooooooooooooooooooooo");
}
