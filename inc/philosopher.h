/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:32 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 18:47:16 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include "../lib/libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				is_setup;
	int				is_alive;
	pthread_t		thid;
	long			last_meal_ms;
	int				nb_meal;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_eat_max;
	struct timeval	time;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	t_philo			**tab_philo;
	pthread_mutex_t	*tab_fork;
	int				is_started;
}					t_data;

typedef struct s_thread_info
{
	t_data			*data;
	int				idx;
}					t_ti;

void				ft_wait_setup(t_data *data);
void				ft_wait_start(int *start);
void				ft_wait_death(t_data *data);
long				ft_get_time_ms(t_data *data);
void				*ft_philo(void *arg);
void				ft_wait_threads(t_data *data);
int					ft_create_threads(t_data *data);

#endif