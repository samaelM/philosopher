/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:42:57 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/24 14:55:20 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief The atoi() function converts the initial
// portion of the string pointed to by nptr to int.
//  The behavior is the same as
//        strtol(nptr, NULL, 10);
//    except that atoi() does not detect errors.
/// @param str The string we want to convert
/// @return The int converted
int	ft_atoi(const char *str)
{
	int		result;
	int		sign;
	size_t	i;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return (result * sign);
}
