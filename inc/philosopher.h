/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:32 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/05 19:36:34 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include "../lib/libft/libft.h"
# include <pthread.h>

typedef struct s_philo
	// rajouter une var pour savoir si il est en vie et ptet aussi pour voir si il a tout manger
{
	int id;
	pthread_t thid;
	long last_meal_ms;
	int nb_meal;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_eat_max;
	struct timeval	time;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	t_philo			**tab_philo;
	pthread_mutex_t	*tab_fork;
	int				is_started;
}					t_data;

typedef struct s_thread_info
{
	t_data			*data;
	int				idx;
}					t_ti;

#endif