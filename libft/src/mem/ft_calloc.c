/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:28:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/25 12:23:35 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/memory.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if ((nmemb > 0 && size > 0))
	{
		if (nmemb / INT_MAX > size)
			return (NULL);
	}
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
