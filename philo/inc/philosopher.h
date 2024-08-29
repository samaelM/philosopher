/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:59:32 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/29 15:46:43 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				is_setup;
	pthread_mutex_t	is_setup_mutex;
	int				is_alive;
	pthread_t		thid;
	long			last_meal_ms;
	int				nb_meal;
	int				f_left;
	int				f_right;
	pthread_mutex_t	*tab_fork;
	pthread_mutex_t	philo_m;
}					t_philo;

typedef struct s_data
{
	int				is_started;
	int				nb_philo;
	int				nb_finished;
	int				nb_eat_max;
	struct timeval	time;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	t_philo			**tab_philo;
	pthread_mutex_t	*tab_fork;
	pthread_mutex_t	data_m;
	pthread_mutex_t	print_m;
}					t_data;

typedef struct s_thread_info
{
	t_data			*data;
	int				idx;
}					t_ti;

void				ft_wait_setup(t_data *data);
int					ft_wait_start(int *start, pthread_mutex_t *start_m);
void				ft_wait_death(t_data *data);
void				*ft_philo(void *arg);
void				ft_wait_threads(t_data *data, int nb);
int					ft_create_threads(t_data *data);
void				ft_print_routine(t_data *data, int id, const char *routine);
int					ft_usleep(unsigned int time);
long int			gettime(void);
int					ft_init(t_data *data, int ac, char **av);
int					is_int(char *str, int nb);
int					ft_check_data(t_data *data, char **av);
int					ft_philo_init(t_philo *arg);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);

#endif
