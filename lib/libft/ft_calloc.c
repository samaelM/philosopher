/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:43:41 by maemaldo          #+#    #+#             */
/*   Updated: 2024/05/24 14:56:23 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief The calloc() function allocates memory for an array of nmemb
// elements of size bytes each and returns a pointer to the allocated
// memory.  The memory is set to zero.  If nmemb or size is 0,
// then calloc() returns either NULL,
// or a unique pointer value that can later be  suc‐
//    cessfully  passed  to  free().   If  the multiplication of nmemb
// and size would result in integer overflow,
// then calloc() returns an error.  By contrast,
// an integer overflow would not be detected in the following call to malloc(),
// with the result that an incorrectly sized
//    block of memory would be allocated:
//        malloc(nmemb * size);
/// @param nmemb
/// @param size
/// @return
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	fsize;

	if (!nmemb || !size)
		return (malloc(0));
	fsize = nmemb * size;
	if ((fsize < size) || (fsize < nmemb))
		return (NULL);
	ptr = malloc(fsize);
	if (!ptr)
		return (NULL);
	return (ft_bzero(ptr, fsize));
}
