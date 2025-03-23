/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:28:22 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 11:31:29 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/memory.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
