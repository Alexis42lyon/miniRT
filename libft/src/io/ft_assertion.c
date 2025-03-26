/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:56:02 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/05 11:56:17 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

int	malloc_assert(void *mem, const char *file, int line)
{
	if (mem)
		return (0);
	ft_dprintf(2, "%s%s:%d: %s: malloc assertion failed%s\n",
		GRAY, file, line, RED, RESET);
	return (-1);
}
