/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:44:23 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/24 14:57:02 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief checks for an alphabetic character;
// in the standard "C" locale, it is equivalent to (isupper(c)
//	|| islower(c)).  In some locales,
//	there may be additional characters for which isalpha() is
// true—letters which are neither uppercase nor lowercase.
/// @param c
/// @return
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
