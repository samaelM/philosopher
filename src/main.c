/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 16:18:07 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

gettimeofday() ne s'update pas tout seul
usleep(1000000); //une seconde
*/

#include "../inc/philosopher.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// int ft_check_death(t_data *data)
// {
// 	while (data->is_started)
// 	{
// 		; //regarde si tout les philo sont en vie,
// doit contenir un mutex pour dieu sais quel raison
// 	}
// }

long	ft_get_time_ms(t_data *data)
{
	gettimeofday(&data->time, NULL);
	return (data->time.tv_sec * 1000 + data->time.tv_usec / 1000);
}

int	ft_eat(t_data *data, int idx)
{
	int	left;
	int	right;

	left = idx;
	right = idx + 1;
	if (idx == data->nb_philo - 1)
		right = 0;
	pthread_mutex_lock(&data->tab_fork[left]);
	printf("%ld %d has taken a fork %d\n", ft_get_time_ms(data), idx, left);
	pthread_mutex_lock(&data->tab_fork[right]);
	printf("%ld %d has taken a fork %d\n", ft_get_time_ms(data), idx, right);
	gettimeofday(&data->time, NULL);
	data->tab_philo[idx]->last_meal_ms = data->time.tv_sec * 1000
		+ data->time.tv_usec / 1000;
	data->tab_philo[idx]->nb_meal++;
	printf("%ld %d is eating with fork %d and %d\n", data->time.tv_sec * 1000
		+ data->time.tv_usec / 1000, idx, left, right);
	usleep(data->time_eat);
	pthread_mutex_unlock(&data->tab_fork[left]);
	pthread_mutex_unlock(&data->tab_fork[right]);
	return (1);
}

void	ft_wait_start(int *start)
{
	while (*start == 0)
		;
}

void	ft_put_pthread(pthread_t n)
{
	long long int	nb;

	nb = (long long int)n;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		nb = (long long int)-n;
	}
	if (nb > 9)
		ft_put_pthread(nb / 10);
	ft_putchar_fd(nb % 10 + '0', 1);
}

t_data	*ft_init(int ac, char **av)
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
	data->time_die = ft_atoi(av[2]) * 1000;
	data->time_eat = ft_atoi(av[3]) * 1000;
	data->time_sleep = ft_atoi(av[4]) * 1000;
	data->tab_philo = malloc(data->nb_philo * sizeof(t_philo *));
	data->is_started = 0;
	gettimeofday(&data->time, NULL);
	data->tab_fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->tab_fork[i], NULL);
		i++;
	}
	return (data);
}

void	*ft_philo(void *arg)
{
	char	*ret;
	t_ti	*info;
	t_data	*data;
	t_philo	*philo;

	info = (t_ti *)arg;
	data = info->data;
	philo = data->tab_philo[info->idx];
	philo->id = info->idx;
	free(info);
	ft_wait_start(&data->is_started);
	while (data->is_started)
	{
		printf("%ld %d is thinking\n", ft_get_time_ms(data), philo->id);
		ft_eat(data, philo->id);
		printf("%d has eaten %d time (max=%d)\n", philo->id, philo->nb_meal,
			data->nb_eat_max);
		printf("%d\n", data->nb_eat_max == philo->nb_meal);
		if (data->nb_eat_max == philo->nb_meal)
		{
			printf("break id %d\n", philo->id);
			break ;
		}
		printf("%ld %d is sleeping\n", ft_get_time_ms(data), philo->id);
		usleep(data->time_sleep);
	}
	ret = ft_itoa(philo->id);
	pthread_exit(ret);
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
	printf("time = %ld\n", data->time.tv_usec);
	while (i < data->nb_philo)
	{
		data->tab_philo[i] = malloc(sizeof(t_philo));
		data->tab_philo[i]->nb_meal = 0;
		info = malloc(sizeof(t_ti));
		info->data = data;
		info->idx = i;
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
	data->is_started = 1;
	printf("----------------start--------------\n");
		// doit ajouter une boucle qui verifie que les philo soit pas mort de faim
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
	return (0);
}
