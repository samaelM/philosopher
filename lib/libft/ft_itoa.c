/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:45:04 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/24 14:57:58 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/// @brief Convert an integer to a string. The function itoa() converts
// the integer value from val into an ASCII representation that will be
// stored under s. The caller is responsible for providing sufficient
// storage in s.
// 	Note
//        The minimal size of the buffer s depends on the choice of
// radix. For example,
// if the radix is 2 (binary),
// you need to supply a buffer with a minimal length of 8 * sizeof (int)
// + 1 characters,
// i.e. one character for each bit plus one for the string terminator. Using a
//        larger radix will require a smaller minimal buffer size.
//    Warning
//        If the buffer is too small, you risk a buffer overflow.
//    Conversion is done using the radix as base,
// which may be a number between 2 (binary conversion) and up to 36.
// If radix is greater than 10,
// the next digit after '9' will be the letter 'a'.
//    If radix is 10 and val is negative, a minus sign will be prepended.
//    The itoa() function returns the pointer passed as s.
/// @param n
/// @return
char	*ft_itoa(int n)
{
	char			*res;
	size_t			len;
	unsigned int	nb;

	len = ft_nbrlen(n);
	res = ft_calloc(len + 1, 1);
	if (!res)
		return (NULL);
	nb = n;
	if (n < 0)
		nb = -n;
	while (len--)
	{
		res[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
