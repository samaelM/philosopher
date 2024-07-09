/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:47:51 by maemaldo          #+#    #+#             */
/*   Updated: 2024/07/09 18:11:30 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

unsigned int	ft_get_time_ms(t_data *data)
{
	gettimeofday(&data->time, NULL);
	return (unsigned int)(data->time.tv_sec * 1000 + data->time.tv_usec / 1000);
}
